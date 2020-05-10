// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Enumerations.h"
#include "TG/Interfaces/CanBeDamaged.h"
#include "TG/Interfaces/Interact.h"
#include "TGCharacter.generated.h"



UCLASS(config=Game)
class ATGCharacter : public APaperCharacter, public ICanBeDamaged
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	virtual void Tick(float DeltaSeconds) override;
protected:


	

	 /* #########################END############################## */

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
public:
	void MoveRight(float Value);
	void BasicAttack();
	void StopAttack();
	void HandleAttack();
	void UpdateCharacter();
	void Interact();





public:
	ATGCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }



	virtual void OnGetDamaged(int32 iBaseDamage, AActor* iAttacker) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ATesting)
		ECharacterStates currentState;


	/* ###########################################################
						Timers
	 ########################################################### */
protected:


	 /* #########################END############################## */


	/* ###########################################################
						Combat
	 ########################################################### */
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACombat)
		float AttackAnimLength;


	 /* #########################END############################## */

	/* ###########################################################
						Debug 
	 ########################################################### */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InteractRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TraceCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InteractTraceSpread;
	//if we make a successful interaction, how many seconds until we can interact again
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InteractTraceCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* interactedActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDidJustInteract;

	void InteractCooldownTimer();

	bool bAnimationFinished = false;

	void CheckForIsNonloopingActionFinished();
	void AttackAnimationChecks();
	void DealDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BasicAttackTraceSpread;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BasicAttackRange;
	//this needs better more accurate checking in future tied with animation frames !!
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BasicAttackCooldown;

	void BasicAttackCooldownTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDidJustBasicAttack;

	int32 basicAttackDamage = 1;
	 /* #########################END############################## */

	
};