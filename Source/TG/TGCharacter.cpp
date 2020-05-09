// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TGCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "TG/Interfaces/Interact.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ATGCharacter

ATGCharacter::ATGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitbox"));
	AttackHitbox->RelativeLocation = AttackHitboxLocation;
	AttackHitbox->SetupAttachment(RootComponent);

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
	GetCharacterMovement()->AirControl = 0;
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
}

void ATGCharacter::OnGetDamaged(float iBaseDamage, AActor* iAttacker)
{
	UE_LOG(LogTemp, Warning, TEXT("Got Damaged"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("BasicAttack", IE_Pressed, this, &ATGCharacter::BasicAttack);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATGCharacter::Interact);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATGCharacter::MoveRight);
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

		//stop attack animation timer
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ATGCharacter::StopAttack, AttackAnimLength, false);
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
// 		TArray<AActor*> OverlappingActors;
// 		AttackHitbox->GetOverlappingActors(OverlappingActors, ATGCharacter::StaticClass());
// 		if (OverlappingActors.Num() > 0)
// 		{
// 
// 		}
	}
}

// Animation

void ATGCharacter::UpdateAnimation()
{
	//this shouldnt have any game logic, just change animations
	if (currentState != ECharacterStates::ATTACKING)
	{

		const FVector PlayerVelocity = GetVelocity();
		const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
		currentState = (PlayerSpeedSqr > 0.0f) ? ECharacterStates::RUNNING : ECharacterStates::IDLE;

	}

	if (currentState == ECharacterStates::ATTACKING)
	{
		UE_LOG(LogTemp, Error, TEXT("check"));
	}



	switch (currentState)
	{
	default:
		break;
	case ECharacterStates::IDLE:
		GetSprite()->SetFlipbook(idleAnimation);
		break;
	case ECharacterStates::WALKING:
		GetSprite()->SetFlipbook(walkingAnimation);
		break;
	case ECharacterStates::RUNNING:
		GetSprite()->SetFlipbook(runningAnimation);
		break;
	case ECharacterStates::ATTACKING:
		GetSprite()->SetFlipbook(basicAttackAnimation);
		break;
	case ECharacterStates::STUNNED:
		GetSprite()->SetFlipbook(stunnedAnimation);
		break;
	case ECharacterStates::DAMAGED:
		GetSprite()->SetFlipbook(damagedAnimation);
		break;
	case ECharacterStates::FALLING:
		GetSprite()->SetFlipbook(fallingAnimation);
		break;
	case ECharacterStates::JUMPING:
		GetSprite()->SetFlipbook(jumpingAnimation);
		break;
	case ECharacterStates::SLIDING:
		GetSprite()->SetFlipbook(slidingAnimation);
		break;
	case ECharacterStates::CROUCHING:
		GetSprite()->SetFlipbook(crouchingAnimation);
		break;
	}
}



void ATGCharacter::Tick(float DeltaSeconds)
{
	//atm disabled
	Super::Tick(DeltaSeconds);

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
	End = PlayerEyesLoc + (PlayerEyesRot.Vector() * InteractDistance);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceComplex = true;
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
	FHitResult HitResult = FHitResult(ForceInit);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, TraceParams))
	{
		if (HitResult.GetActor() != nullptr)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteract::StaticClass()))
			{
				//play success sound?

				//since its here not above scope it will only show actors with the interact interface only 
				interactedActor = HitResult.GetActor();

				IInteract* Interact = Cast<IInteract>(interactedActor);
				if (Interact != nullptr)
				{
					Interact->Interact(this);
				}
			}
		}
	}
}
