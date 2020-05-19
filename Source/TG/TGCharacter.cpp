// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TGCharacter.h"
#include "TG/TG.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "TG/GameInstance/TGGameInstance.h"
#include "TG/NPCs/MasterNPC.h"
#include "TG/Components/InventoryComponent.h"
#include "Components/AbilityComponent.h"


//////////////////////////////////////////////////////////////////////////
// ATGCharacter

ATGCharacter::ATGCharacter()
{

	/* ###########################################################
						DATA
########################################################### */
/*load object stats datatable automatically, datatable values are in beginplay*/
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerDataDTObject(TEXT("DataTable'/Game/TG/BP/Data/DT_PlayerData.DT_PlayerData'"));
	if (PlayerDataDTObject.Succeeded())
	{

		//Use CharacterStatsDataTable to access the table data
		DataTableObjectData = PlayerDataDTObject.Object;
	}
	/* #########################END############################## */

	GetSprite()->SetRelativeScale3D(TG_SPRITE_SCALE);

	PrimaryActorTick.bCanEverTick = true;


	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 3.0f;
	GetCharacterMovement()->AirControl = 0.1;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;


	GetSprite()->SetIsReplicated(true);
	bReplicates = true;


	/*currentFlipbook = idleAnimation;*/

	npcDetectComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("npcDetectComponent"));
	npcDetectComponent->SetupAttachment(RootComponent);
	npcDetectComponent->SetBoxExtent(FVector(600, 50, 600));
	npcDetectComponent->OnComponentBeginOverlap.AddDynamic(this, &ATGCharacter::OnNpcDetectCompBeginOverlap);
	npcDetectComponent->OnComponentEndOverlap.AddDynamic(this, &ATGCharacter::OnNpcDetectCompEndOverlap);
	


	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
	abilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	/* ###########################################################
						DEFAULT VALUES
	 ########################################################### */
	initializeTimer = 0.1f;

	AttackAnimLength = 1.0f;
	InteractRange = 300.0f;
	InteractTraceSpread = 0.5f;
	TraceCount = 10;
	bDidJustInteract = false;
	InteractTraceCooldown = 1.0f;
	BasicAttackRange = 150;
	BasicAttackTraceSpread = 0.5;
	BasicAttackCooldown = 0.3f;
	bDidJustBasicAttack = false;


	 /* #########################END############################## */
}

void ATGCharacter::StartInitializeTimer()
{
	FTimerHandle TGCharacterInitializeTimer;
	GetWorld()->GetTimerManager().SetTimer(TGCharacterInitializeTimer, this, &ATGCharacter::InitializeDelayed,
		initializeTimer, false);
}

void ATGCharacter::InitializeDelayed()
{
	InitializeDataTableInfo();
	PassDataFromTableToObjectVariables();
}

void ATGCharacter::InitializeDataTableInfo()
{
	FPlayerData* PlayerData = DataTableObjectData->FindRow<FPlayerData>(
		DataTableObjectRowNames[DTPlayerDataRowNumber], "TGCharacter ObjectData", true);
	if (PlayerData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectData LOADED SUCCESSFULLY."));
		currentPlayerStats = PlayerData->playerStats;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectData load FAILED"));
	}
}

void ATGCharacter::InitializeReferences()
{

}

void ATGCharacter::PassDataFromTableToObjectVariables()
{

}

void ATGCharacter::InitializeStates()
{

	currentState = ECharacterStates::IDLE;
	currentPlayerState = EPlayerExploringStates::EXPLORING;
	Cast<UTGGameInstance>(GetGameInstance())->SetTGGameState(ETGGameState::INGAMEEXPLORE);
}

void ATGCharacter::InteractCooldownTimer()
{
	bDidJustInteract = false;
}


void ATGCharacter::CheckForIsNonloopingActionFinished()
{
	if (currentState == ECharacterStates::ATTACKING)
	{
		AttackAnimationChecks();
	}
}

void ATGCharacter::AttackAnimationChecks()
{
	int32 currentAnimationLength = this->GetSprite()->GetFlipbookLengthInFrames() - 1;
	int32 CurrentAnimationFrame = this->GetSprite()->GetPlaybackPositionInFrames();
	//deal damage at this frame
	if (CurrentAnimationFrame == currentAnimationLength - 6) //deals damage only at this frame
	{
		DealDamage();
	}

	//attack is finished
	if (CurrentAnimationFrame >= currentAnimationLength)
	{
		StopAttack();
	}
}

// !! do checks later for events when we hit multiple different actors at once. store array of lasthits and compare them etc
void ATGCharacter::DealDamage()
{
	FVector Start;
	FVector End;
	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;
	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);
	Start = PlayerEyesLoc;
	/*End = Start + (PlayerEyesRot.Vector() * InteractDistance);*/ //normal
	for (int i = 0; i < TraceCount; i++)
	{
		End = Start + (FMath::VRandCone(PlayerEyesRot.Vector(), BasicAttackTraceSpread, BasicAttackTraceSpread)) * BasicAttackRange; //with spread
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		DrawDebugLine(GetWorld(), Start, End, FColor::Green , false, 1.0f, 0, 3.0f);
		FHitResult HitResult = FHitResult(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, TraceParams))
		{
			if (HitResult.GetActor() != nullptr)
			{
				if (HitResult.GetActor()->GetClass()->ImplementsInterface(UCanBeDamaged::StaticClass()) &&
					!bDidJustBasicAttack)
				{
					//if we did successful interact with interface we need to make sure it only did it once
					bDidJustBasicAttack = true;
					FTimerHandle justBasicAttackedTimer;
					GetWorld()->GetTimerManager().SetTimer(justBasicAttackedTimer, this, &ATGCharacter::BasicAttackCooldownTimer, BasicAttackCooldown, false);

					//play success sound?

					//since its here not above scope it will only show actors with the interact interface only 
					interactedActor = HitResult.GetActor();

					ICanBeDamaged* dmgInterface = Cast<ICanBeDamaged>(interactedActor);
					if (dmgInterface != nullptr)
					{
						dmgInterface->OnGetDamaged(currentPlayerStats.AttackDamage, this);
					}
				}
			}
		}
	}
}

void ATGCharacter::BasicAttackCooldownTimer()
{
	bDidJustBasicAttack = false;
}

void ATGCharacter::OnGetDamaged(int32 iBaseDamage, AActor* iAttacker)
{
		if (iBaseDamage >= 0)
	 	{
	 		currentPlayerStats.currentHealth -= iBaseDamage;
	 		UE_LOG(LogTemp, Warning, TEXT("Player damaged, %i health remaining."), currentPlayerStats.currentHealth);
			CheckForDeath();
	 	}
}

void ATGCharacter::MoveRight(float Value)
{
	if (currentState != ECharacterStates::ATTACKING)
	{
		// Apply the input to the character motion
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
		if (Value == 0)
		{
			currentState = ECharacterStates::IDLE;
		}

		if (Value != 0)
		{
			currentState = ECharacterStates::RUNNING;
			UpdateCharacter();
		}

		if (Value < 0.0f)
		{
			bIsFacingRight = false;
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (Value > 0.0f)
		{
			bIsFacingRight = true;
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		UpdateCharacter();
	}
}



void ATGCharacter::BasicAttack()
{
	if (currentState != ECharacterStates::ATTACKING &&
		currentState != ECharacterStates::JUMPING)
	{
		currentState = ECharacterStates::ATTACKING;
		UpdateCharacter();

		/*tick checks if our state animation is finished and stops the animation at last frame*/

	}
}

void ATGCharacter::StopAttack()
{
	
	currentState = ECharacterStates::IDLE;
	UpdateCharacter();
}



void ATGCharacter::SetDataTableObjectDataRowNames()
{
	if (DataTableObjectData != nullptr)
	{
		DataTableObjectRowNames = DataTableObjectData->GetRowNames();
	}
}

// Animation

void ATGCharacter::UpdateAnimation()
{
	
	//this shouldnt have any game logic, just change animations
	if (currentState != ECharacterStates::ATTACKING)
	{
		GetSprite()->SetLooping(true);
		const FVector PlayerVelocity = GetVelocity();
		const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
		currentState = (PlayerSpeedSqr > 0.0f) ? ECharacterStates::RUNNING : ECharacterStates::IDLE;

	}
	/*every state where we want to play the animation only once, we just set it to not loop here,
	so we dont have to make a spaghetti of timers, only ones mostly that shouldn't be looping are 
	stuff like death, attacks etc that should only play once and then go to another state when
	completed*/

	switch (currentState)
	{
	default:
		break;
	case ECharacterStates::IDLE:
		
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(idleAnimation);
		break;
	case ECharacterStates::WALKING:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(walkingAnimation);
		break;
	case ECharacterStates::RUNNING:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(runningAnimation);
		break;
	case ECharacterStates::ATTACKING:
		GetSprite()->SetLooping(false);
		GetSprite()->PlayFromStart();
		GetSprite()->SetFlipbook(basicAttackAnimation);
		break;
	case ECharacterStates::STUNNED:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(stunnedAnimation);
		break;
	case ECharacterStates::DAMAGED:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(damagedAnimation);
		break;
	case ECharacterStates::FALLING:
		GetSprite()->SetLooping(false);
		GetSprite()->SetFlipbook(fallingAnimation);
		break;
	case ECharacterStates::JUMPING:
		GetSprite()->SetLooping(false);
		GetSprite()->SetFlipbook(jumpingAnimation);
		break;
	case ECharacterStates::SLIDING:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(slidingAnimation);
		break;
	case ECharacterStates::CROUCHING:
		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(crouchingAnimation);
		break;
	case ECharacterStates::DEAD:
		GetSprite()->SetLooping(false);
		GetSprite()->SetFlipbook(deathAnimation);
		break;
	}
}

class UInventoryComponent* ATGCharacter::GetInventoryComponent()
{
	return inventoryComponent;
}

class UAbilityComponent* ATGCharacter::GetAbilityComponent()
{
	return abilityComponent;
}

void ATGCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//keeps the actor at the right position in 2d in editor
	FTransform trans = this->GetActorTransform();
	FVector loc = trans.GetLocation();
	loc.Y = -1; //so it wouldn't clip
	trans.SetLocation(loc);
	this->SetActorTransform(trans);
}

void ATGCharacter::Tick(float DeltaSeconds)
{
	//atm disabled
	Super::Tick(DeltaSeconds);

	CheckForIsNonloopingActionFinished();
	
}




void ATGCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeStates();
	StartInitializeTimer();
	InitializeReferences();
	SetDataTableObjectDataRowNames();
}

void ATGCharacter::OnNpcDetectCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteract* InteractionInterface = Cast<IInteract>(OtherActor);
	if (InteractionInterface)
	{
		InteractionInterface->OnEnterPlayerRadius(this);
	}
}

void ATGCharacter::OnNpcDetectCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IInteract* InteractionInterface = Cast<IInteract>(OtherActor);
	if (InteractionInterface)
	{
		InteractionInterface->OnLeavePlayerRadius(this);
	}
}

void ATGCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();
}

void ATGCharacter::Interact()
{
	FVector Start;
	FVector End;
	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;
	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);
	Start = PlayerEyesLoc;
	/*End = Start + (PlayerEyesRot.Vector() * InteractDistance);*/ //normal
	for (int i = 0; i < TraceCount; i++)
	{
		End = Start + (FMath::VRandCone(PlayerEyesRot.Vector(), InteractTraceSpread, InteractTraceSpread)) * InteractRange; //with spread
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 3.0f);
		FHitResult HitResult = FHitResult(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, TraceParams))
		{
			if (HitResult.GetActor() != nullptr)
			{
				if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteract::StaticClass()) &&
					!bDidJustInteract)
				{
					//if we did successful interact with interface we need to make sure it only did it once
					bDidJustInteract = true;
					FTimerHandle justInteractedTimer;
					GetWorld()->GetTimerManager().SetTimer(justInteractedTimer,this, &ATGCharacter::InteractCooldownTimer, InteractTraceCooldown, false);

					//play success sound?

					//since its here not above scope it will only show actors with the interact interface only 
					interactedActor = HitResult.GetActor();

					IInteract* interactInterface = Cast<IInteract>(interactedActor);
					if (interactInterface != nullptr)
					{
						interactInterface->Interact(this);
					}
				}
			}
		}
	}
}

void ATGCharacter::CheckForDeath()
{
	if (currentPlayerStats.currentHealth <= 0)
	{
		
		//play death animation and in 10 seconds fall through the ground and destroy self
		currentState = ECharacterStates::DEAD;
		UpdateAnimation();

		//give xp & drop loot?

		//here we can add some effect in future for disappearing corpses

		
	}
}

void ATGCharacter::CastAbility()
{

}
