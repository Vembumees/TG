// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SGPawn.h"
#include "SGProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/InteractInterface.h"
#include "Kismet/KismetMathLibrary.h"



ASGPawn::ASGPawn()
{	
	
	
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetupAttachment(RootComponent);
	ShipMeshComponent->AddLocalRotation(FQuat(0, 0, 90, 0));
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(ShipMeshComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanAttack = true;

	forwardVec = FVector(1.f, 0.f, 0.f);
	rightVec = FVector(0.f, 1.f, 0.f);
}

void ASGPawn::OnGetDamaged(float iBaseDamage, AActor* iAttacker)
{

}

void ASGPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGPawn::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASGPawn::Attack);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASGPawn::Interact);
}

void ASGPawn::Tick(float DeltaSeconds)
{
	
}

void ASGPawn::Attack()
{
	// If it's ok to fire again
	if (bCanAttack == true)
	{

			
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<ASGProjectile>(BP_SGProjectile, SpawnLocation, UKismetMathLibrary::Conv_VectorToRotator(-GetActorRightVector()));
			}

			bCanAttack = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ASGPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanAttack = false;
	
	}
}

void ASGPawn::ShotTimerExpired()
{
	bCanAttack = true;
}

void ASGPawn::MoveForward(float iVal)
{
	//using this left vector to move this mesh to forward.
	ShipMeshComponent->AddForce(impulseForce * (ShipMeshComponent->GetRightVector() * -1) * iVal);
}

void ASGPawn::MoveRight(float iVal)
{
	
	ShipMeshComponent->AddRelativeRotation(FRotator(0, iVal, 0));
}

void ASGPawn::Interact()
{
	AActor* Caller = this;
	FVector l_loc = GetActorLocation();
	FRotator l_rot = UKismetMathLibrary::Conv_VectorToRotator(-GetActorRightVector());
	FVector TraceEnd = (l_loc  + l_rot.Vector() * linetraceDistance);
	FCollisionQueryParams Queryparams;
	Queryparams.AddIgnoredActor(this);
	Queryparams.bTraceComplex = true;

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, 
		l_loc,
		TraceEnd, 
		ECollisionChannel::ECC_WorldDynamic, 
		Queryparams))
	{
		if (HitResult.GetActor() != nullptr)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				UGameplayStatics::PlaySoundAtLocation(this, SFXInteractSuccess, GetActorLocation());
				interactedActor = HitResult.GetActor();
				
				IInteractInterface* IT = Cast<IInteractInterface>(interactedActor);
				if (IT != nullptr)
				{
					IT->Interact(this);
				}
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this, SFXInteractFail, GetActorLocation());
			}
		}
	}
}
