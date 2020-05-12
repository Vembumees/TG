// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Interfaces/Interact.h"
#include "Engine/DataTable.h"
#include "MasterNPC.generated.h"

//stats that every object we inherit from this has
USTRUCT(BlueprintType)
struct FNPCStats
{
	GENERATED_BODY()

		FNPCStats()
	{
		npcName = FText::FromString("Smugger");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText npcName;
};



USTRUCT(BlueprintType)
struct FNPCDialogues
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText npcName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> dialogueMessages;

};

USTRUCT(BlueprintType)
struct FNPCData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FNPCStats npcStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FNPCDialogues npcDialogues;
};

UCLASS()
class TG_API AMasterNPC : public APaperCharacter, public IInteract
{
	GENERATED_BODY()

		AMasterNPC();

protected:
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* dialogueAlert;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* dialogueComp;	//dont forget to set the widget in the blueprint

public:
	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;

	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;

	virtual void Interact(AActor* iPlayer) override;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/* ###########################################################
						References
	 ########################################################### */
	class UDialogueWidget* refDialogueWidget;

	 /* #########################END############################## */

protected:

	void RotateTowardsPlayer(AActor* iPlayer);

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
		int32 DTNPCDataRowNumber;
	//ANIMATIONS

	//STATS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FNPCStats currentNPCStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FNPCDialogues currentNPCDialogues;
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
	/* #########################END############################## */


	/* ###########################################################
					Animations
 ########################################################### */
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* idleAnimation;

	

	/* ###########################################################
						Dialogue
	 ########################################################### */
protected:
	UPROPERTY(EditAnywhere)
		TArray<FNPCDialogues> dialogueMessages;

	void ShowNextDialogueMessage();

	void InitDialogueMessageHack();
	int32 simpleDialogueCounter;
	 /* #########################END############################## */
};
