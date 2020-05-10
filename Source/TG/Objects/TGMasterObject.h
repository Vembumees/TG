// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Engine/DataTable.h"
#include "TG/Interfaces/Interact.h"
#include "TG/Interfaces/CanBeDamaged.h"
#include "TGMasterObject.generated.h"

//stats that every object we inherit from this has
USTRUCT(BlueprintType)
struct FObjectBasicStats : public FTableRowBase
{
	GENERATED_BODY()

		FObjectBasicStats()
	{
		objectName = FText::FromString("Object");
		maxHealth = 3;
		currentHealth = maxHealth;
		bIsDamaged = false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText objectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDamaged;
};

//animations that every object we inherit from this has
USTRUCT(BlueprintType)
struct FObjectBasicAnimations : public FTableRowBase
{
	GENERATED_BODY()

		//object default animation
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbook* ObjectIdleAnimation;
	//when the object is damaged
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbook* ObjectHitAnimation;
	//object is destroyed animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbook* ObjectDestroyedAnimation;
	//when object is interacted or selected with animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbook* ObjectInteractedAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPaperFlipbook* ObjectMiscInteractionAnimation;
};

USTRUCT(BlueprintType)
struct FObjectData : public FTableRowBase
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FObjectBasicStats objectStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FObjectBasicAnimations objectBasicAnimations;
};

UCLASS()
class TG_API ATGMasterObject : public AActor, public IInteract, public ICanBeDamaged
{
	GENERATED_BODY()

public:
	ATGMasterObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class USceneComponent* objectRootComp;
	// 		//since we're using PaperCharacter for objects and capsulecollision is crap, making boxcollisioncomp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class UBoxComponent* boxCollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class UPaperFlipbookComponent* SpriteComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class UAudioComponent* audioComp;




	/* ###########################################################
					Interface functions
 ########################################################### */
	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;
	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;
	virtual void Interact(AActor* iPlayer) override;
	virtual void OnGetDamaged(int32 iBaseDamage, AActor* iAttacker) override;


	virtual void OnConstruction(const FTransform& Transform) override;

	/* #########################END############################## */


protected:
	virtual void BeginPlay() override;

	/* ###########################################################
						Initialize & References
	 ########################################################### */
	 //init sprites etc ingame

	void StartInitializeTimer();
	void InitializeDelayed();
	void InitializeDataTableInfo();
	void InitializeReferences();

	void PassDataFromTableToObjectVariables();

	UPROPERTY(EditAnywhere)
		float initializeTimer;
	/* #########################END############################## */


   /* ###########################################################
					   Data
	########################################################### */

	void SetDataTableObjectDataRowNames();

	UPROPERTY()
		class UDataTable* DataTableObjectData;
	UPROPERTY()
		TArray<FName> DataTableObjectRowNames;
	/*Enter the row you want the object to use starts from 0, could also make it a string later*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		int32 DTObjectStatsRowNumber;
	//ANIMATIONS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FObjectBasicAnimations currentBasicAnimations;
	//STATS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FObjectBasicStats currentBasicStats;
	//SOUND?

	 /* #########################END############################## */


protected:

	UPROPERTY(EditAnywhere)
		float objectDeathTimer;
};
