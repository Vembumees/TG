// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Enumerations.h"
#include "TG/Interfaces/CanBeDamaged.h"
#include "TG/Interfaces/Interact.h"
#include "Engine/DataTable.h"
#include "TGCharacter.generated.h"

//stats that every object we inherit from this has
USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

		FPlayerStats()
	{
		characterName = FText::FromString("Object");
		maxHealth = 3;
		currentHealth = maxHealth;
		AttackDamage = 1;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText characterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AttackDamage;
		
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FPlayerStats playerStats;
};

UCLASS(config=Game)
class ATGCharacter : public APaperCharacter, public ICanBeDamaged
{
	GENERATED_BODY()

public:
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* npcDetectComponent;

	class UInventoryComponent* GetInventoryComponent();



	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	UFUNCTION()
	void OnNpcDetectCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32  OtherBodyIndex, bool  bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnNpcDetectCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32  OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AInventory)
		class UInventoryComponent* inventoryComponent;
	/* ###########################################################
						Animations
	 ########################################################### */
protected:
	
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

   /* ###########################################################
					   Data
	########################################################### */

	void SetDataTableObjectDataRowNames();

	UPROPERTY()
		class UDataTable* DataTableObjectData;
	UPROPERTY()
		TArray<FName> DataTableObjectRowNames;
	/*Row number and take 1 off from it. Making it do it automatically in all code is too much extra complexity.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		int32 DTPlayerDataRowNumber;
	//ANIMATIONS

	//STATS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FPlayerStats currentPlayerStats;
	//SOUND?

	 /* #########################END############################## */

	/* ###########################################################
						Initialize & References
	 ########################################################### */
protected:
	//init sprites etc ingame

	void StartInitializeTimer();
	void InitializeDelayed();
	void InitializeDataTableInfo();
	void InitializeReferences();
	void PassDataFromTableToObjectVariables();

	UPROPERTY(EditAnywhere)
		float initializeTimer;
public:
	class AMasterNPC* refCurrentlyInteractingNPC;
	/* #########################END############################## */

	protected:
	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();
public:
	void MoveRight(float Value);
	void BasicAttack();
	void StopAttack();
	void UpdateCharacter();
	void Interact();
	void CheckForDeath();





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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ATesting)
		EPlayerExploringStates currentPlayerState;

	void InitializeStates();





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

	 /* #########################END############################## */

	
};
