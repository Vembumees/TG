// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TGCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ATGCharacter

ATGCharacter::ATGCharacter()
{
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

    	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
        	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
         	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
         	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
         	TextComponent->SetupAttachment(RootComponent);

	
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	currentState = ECharacterStates::IDLE;
	
	/*currentFlipbook = idleAnimation;*/
}

// Animation

void ATGCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
 	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
		currentState = (PlayerSpeedSqr > 0.0f) ? ECharacterStates::RUNNING : ECharacterStates::IDLE;


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

	/*GetSprite()->PlayFromStart();*/
}

void ATGCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATGCharacter::MoveRight);
}

void ATGCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}



void ATGCharacter::BasicAttack()
{

}

void ATGCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}
