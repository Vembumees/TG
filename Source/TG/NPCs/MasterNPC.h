// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Interfaces/Interact.h"
#include "TG/Enumerations.h"
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

		FNPCDialogues() {
		dialogueMessages.Add(FText::FromString("Hello!"));
		dialogueMessages.Add(FText::FromString("Hey!"));
		dialogueMessages.Add(FText::FromString("Ok enough said."));

		dialogueMessagesRumor.Add(FText::FromString("Event1 Rumor"));
		dialogueMessagesRumor.Add(FText::FromString("Event2 Rumor"));
		dialogueMessagesRumor.Add(FText::FromString("Event3 Rumor"));
		dialogueMessagesRumor.Add(FText::FromString("Event4 Rumor"));

		dialogueMessagesHasDoneEvent1.Add(FText::FromString("Event1 message"));
		dialogueMessagesHasDoneEvent2.Add(FText::FromString("Event2 message"));
		dialogueMessagesHasDoneEvent3.Add(FText::FromString("Event3 message"));
		dialogueMessagesHasDoneEvent4.Add(FText::FromString("Event4 message"));

		dialogueMessagesPlayerHasDoneAllTasks.Add(FText::FromString("AllEventsCompleted"));
		dialogueSelectionMenuButtons.AddUnique(EDialogueSelectButtons::TALK);
		}

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText npcName;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessages;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesRumor;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesHasDoneEvent1;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesHasDoneEvent2;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesHasDoneEvent3;

	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesHasDoneEvent4;
	UPROPERTY(EditAnywhere)
		TArray<FText> dialogueMessagesPlayerHasDoneAllTasks;
	//buttons that this npc has when interacted with, talk, trade etc
	UPROPERTY(EditAnywhere)
		TArray<EDialogueSelectButtons> dialogueSelectionMenuButtons;

};

USTRUCT(BlueprintType)
struct FNPCData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = ADialogue)
		FNPCStats npcStats;

	UPROPERTY(EditAnywhere, Category = ADialogue)
		FNPCDialogues npcDialogues;
};

UCLASS()
class TG_API AMasterNPC : public APaperCharacter, public IInteract
{
	GENERATED_BODY()

		AMasterNPC();

public:
	friend class UDialogueSelectButton; // for dialogue stuff so it can access friend functions

protected:
	UPROPERTY(VisibleDefaultsOnly)
	class UPaperFlipbookComponent* dialogueAlert;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* dialogueSelectionComp;	//dont forget to set the widget in the blueprint

public:
	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;

	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;

	virtual void Interact(AActor* iPlayer) override;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

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
	/*Row number and take 1 off from it. Making it do it automatically in all code is too much extra complexity.*/
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

public:
	UPROPERTY()
	class UDialogueSelectionMenu* refDialogueSelectionMenu;
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
	//this holds all dialogues
	UPROPERTY(EditAnywhere)
		TArray<FNPCDialogues> dialogueMessages;

	void InitDialogueMessageHack();

	void ShowNextDialogueMessage();

	void SetDialogueSelectInvisible();
	void SetDialogueSelectVisible();

	int32 simpleDialogueCounter;
	int32 simpleDialogueCounterEvent1;
	int32 simpleDialogueCounterEvent2;
	int32 simpleDialogueCounterEvent3;
	int32 simpleDialogueCounterEvent4;

	UPROPERTY(EditAnywhere, Category = ADialogue)
	bool bDoesDialogueLoop;
	bool bIsDialogueExhausted;

	UPROPERTY(EditAnywhere, Category = ADialogue)
	bool bHasPlayerDoneEvent1;
	UPROPERTY(EditAnywhere, Category = ADialogue)
	bool bHasPlayerDoneEvent2;
	UPROPERTY(EditAnywhere, Category = ADialogue)
	bool bHasPlayerDoneEvent3;
	UPROPERTY(EditAnywhere, Category = ADialogue)
	bool bHasPlayerDoneEvent4;

	bool bEvent1DialogueFinished;
	bool bEvent2DialogueFinished;
	bool bEvent3DialogueFinished;
	bool bEvent4DialogueFinished;


	//refactor functions
	void GreetingsLoopMessage();
	void GreetingsNonLoopMessage();
	void ExhaustedDialogue();
	void Event1Dialogue();
	void Event2Dialogue();
	void Event3Dialogue();
	void Event4Dialogue();
	void AllEventsFinishedDialogue();

	//DialogueSelectionMenu
	void CreateDialogueSelection();

	 /* #########################END############################## */
};
