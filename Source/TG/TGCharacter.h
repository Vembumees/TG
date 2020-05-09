// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Enumerations.h"
#include "TGCharacter.generated.h"

class UTextRenderComponent;

/**
 * This class is the default character for TG, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class ATGCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACombat)
		class UBoxComponent* AttackHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACombat)
		FVector AttackHitboxLocation = FVector(80.0f, 0, 0);


	/* ###########################################################
						Animations
	 ########################################################### */
	 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=  Animations)
		class UPaperFlipbook* runningAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* walkingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* idleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* jumpingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* fallingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* deathAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* stunnedAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* damagedAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* basicAttackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* crouchingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* slidingAnimation;
	
	/* #########################END############################## */


	/* ###########################################################
						Sounds
	 ########################################################### */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* runningSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* walkingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* jumpingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* deathSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* damagedSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sounds)
		USoundBase* basicAttackSound;






	 /* #########################END############################## */


	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();
	void MoveRight(float Value);
	void BasicAttack();
	void StopAttack();
	void HandleAttack();
	void UpdateCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


public:
	ATGCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ATesting)
		ECharacterStates currentState;


	/* ###########################################################
						Timers
	 ########################################################### */
protected:
	FTimerHandle AttackTimerHandle;

	 /* #########################END############################## */


	/* ###########################################################
						Combat
	 ########################################################### */
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACombat)
		float AttackAnimLength = 1.0f;


	 /* #########################END############################## */

	
};
