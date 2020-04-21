// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/CollisionProfile.h"
#include "SpaceGame/SpaceGameProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASGPlayerPawn::ASGPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetupAttachment(RootComponent);
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	/* ###########################################################
							Default values
	 ########################################################### */
	bCanAttack = true;
	attackRate = 0.1f;


}

// Called when the game starts or when spawned
void ASGPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASGPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If non-zero size, move this actor
// 	if (Movement.SizeSquared() > 0.0f)
// 	{
// 		const FRotator NewRotation = Movement.Rotation();
// 		FHitResult Hit(1.f);
// 		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
// 
// 		if (Hit.IsValidBlockingHit())
// 		{
// 			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
// 			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
// 			RootComponent->MoveComponent(Deflection, NewRotation, true);
// 		}
// 	}

}

void ASGPlayerPawn::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	// If it's ok to fire again
	if (bCanAttack == true)
	{
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(FVector(20,0,0));

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<ASpaceGameProjectile>(SpawnLocation, GetActorRotation());
			}

			World->GetTimerManager().SetTimer(AttackExpireTimer, this, &ASGPlayerPawn::AttackTimerExpired, attackRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanAttack = false;
		
	}
}



void ASGPlayerPawn::AttackTimerExpired()
{
	bCanAttack = true;
}

void ASGPlayerPawn::Interact()
{

}

void ASGPlayerPawn::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		SetActorLocation();
		
	}
}

void ASGPlayerPawn::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(this->GetActorForwardVector(), Val);
	}
}

