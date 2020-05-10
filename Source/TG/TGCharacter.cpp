// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TGCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ATGCharacter

ATGCharacter::ATGCharacter()
{
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

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;


	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	currentState = ECharacterStates::IDLE;

	/*currentFlipbook = idleAnimation;*/



	/* ###########################################################
						DEFAULT VALUES
	 ########################################################### */
	AttackAnimLength = 1.0f;
	InteractRange = 300.0f;
	InteractTraceSpread = 0.5f;
	TraceCount = 10;
	bDidJustInteract = false;
	InteractTraceCooldown = 1.0f;
	BasicAttackRange = 150;
	BasicAttackTraceSpread = 0.5;
	BasicAttackCooldown = 1.0f;
	bDidJustBasicAttack = false;


	 /* #########################END############################## */
}



void ATGCharacter::OnGetDamaged(int32 iBaseDamage, AActor* iAttacker)
{

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

//Todo do checks later for events when we hit multiple different actors at once. store array of lasthits and compare them etc
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
						dmgInterface->OnGetDamaged(basicAttackDamage, this);
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
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (Value > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		UpdateCharacter();
	}
}



void ATGCharacter::BasicAttack()
{
	UE_LOG(LogTemp, Error, TEXT("atk"));
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

void ATGCharacter::HandleAttack()
{
	if (currentState == ECharacterStates::ATTACKING)
	{
		//TODO do this later, will implement interactable object first
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

	if (currentState == ECharacterStates::ATTACKING)
	{
		UE_LOG(LogTemp, Error, TEXT("check"));
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
		GetSprite()->SetFlipbook(crouchingAnimation);
		break;
	}
}



void ATGCharacter::Tick(float DeltaSeconds)
{
	//atm disabled
	Super::Tick(DeltaSeconds);

	CheckForIsNonloopingActionFinished();
	
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
