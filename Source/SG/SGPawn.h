// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGPawn.generated.h"

UCLASS(Blueprintable)
class ASGPawn : public  APawn
{
	GENERATED_BODY()

public:


	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	ASGPawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;
	
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;



	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	/* Fire a shot in the specified direction */
	void Attack();

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

private:

	/* Flag to control firing  */
	uint32 bCanAttack : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }





	/* ###########################################################
					movement
 ########################################################### */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACustom")
		FVector Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACustom")
		float MoveSpeed;

	float forwardVal;
	float rightVal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACustom")
	float impulseForce = 10000;
	FVector forwardVec;
	FVector rightVec;

public:

	void MoveForward(float iVal);
	void MoveRight(float iVal);
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SFXInteractSuccess;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* SFXInteractFail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* interactedActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ASGProjectile> BP_SGProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACustom - Gameplay")
		float linetraceDistance;
};

