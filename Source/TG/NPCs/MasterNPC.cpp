// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterNPC.h"
#include "TG/TG.h"
#include "PaperFlipbookComponent.h"
#include "Components/WidgetComponent.h"
#include "TG/UI/Dialogue/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "TG/UI/Dialogue/DialogueSelectionMenu.h"
#include "TG/TGCharacter.h"

AMasterNPC::AMasterNPC()
{

	/* ###########################################################
					DATA
	########################################################### */
	/*load object stats datatable automatically, datatable values are in beginplay*/
	static ConstructorHelpers::FObjectFinder<UDataTable> NPCDataDTObject(TEXT("DataTable'/Game/TG/BP/Data/DT_NPCData.DT_NPCData'"));
	if (NPCDataDTObject.Succeeded())
	{

		//Use CharacterStatsDataTable to access the table data
		DataTableObjectData = NPCDataDTObject.Object;
	}
	/* #########################END############################## */


	dialogueAlert = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("dialogueAlert"));
	dialogueAlert->SetupAttachment(RootComponent);
	dialogueAlert->SetRelativeLocation(FVector(30, 0, 150));
	dialogueAlert->SetRelativeScale3D(FVector(3, 3, 3));
	dialogueAlert->SetVisibility(false);

	//sets our character sprite default scale
	GetSprite()->SetRelativeScale3D(TG_SPRITE_SCALE);

	dialogueSelectionComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("dialogueSelectionComp"));
	dialogueSelectionComp->SetupAttachment(RootComponent);
	dialogueSelectionComp->SetRelativeLocation(FVector(0, 0, 150));
	dialogueSelectionComp->SetVisibility(true);
	dialogueSelectionComp->SetCollisionProfileName(TEXT("NoCollision"));
	dialogueSelectionComp->SetGenerateOverlapEvents(false);
	dialogueSelectionComp->SetWidgetSpace(EWidgetSpace::Screen);

	/* ###########################################################
						default values
	 ########################################################### */
	initializeTimer = 0.1f;

	//dialogue
	simpleDialogueCounter = 0;
	bDoesDialogueLoop = true;
	bIsDialogueExhausted = false;

	//dialogue - events
	bHasPlayerDoneEvent1 = false;
	bHasPlayerDoneEvent2 = false;
	bHasPlayerDoneEvent3 = false;
	bHasPlayerDoneEvent4 = false;

	bEvent1DialogueFinished = false;
	bEvent2DialogueFinished = false;
	bEvent3DialogueFinished = false;
	bEvent4DialogueFinished = false;

	simpleDialogueCounterEvent1 = 0;
	simpleDialogueCounterEvent2 = 0;
	simpleDialogueCounterEvent3 = 0;
	simpleDialogueCounterEvent4 = 0;

	/* #########################END############################## */
}

void AMasterNPC::OnEnterPlayerRadius(AActor* iPlayer)
{
	dialogueAlert->SetVisibility(true);
	RotateTowardsPlayer(iPlayer);




}

void AMasterNPC::OnLeavePlayerRadius(AActor* iPlayer)
{
	dialogueAlert->SetVisibility(false); //this cliches right now a bit when disappearing it, needs animation in future

	SetDialogueSelectInvisible();

}

void AMasterNPC::Interact(AActor* iPlayer)
{
	//give our reference to the player, this only works with TGCharacter !!

	AddsMasterNPCRefToPlayer(iPlayer);
	RotateTowardsPlayer(iPlayer);
	dialogueAlert->SetVisibility(false);
	CreateDialogueSelection();
	SetDialogueSelectVisible();
// 	FTimerHandle interactTimer;
// 	GetWorld()->GetTimerManager().SetTimer(interactTimer, this, &AMasterNPC::CreateDialogueSelection, 0.5f, false);

}

void AMasterNPC::BeginPlay()
{
	Super::BeginPlay();
	StartInitializeTimer();
	InitializeReferences();
	SetDataTableObjectDataRowNames();


	


}

void AMasterNPC::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//keeps the actor at the right position in 2d in editor
	FTransform trans = this->GetActorTransform();
	FVector loc = trans.GetLocation();
	loc.Y = -1; //so it wouldn't clip
	trans.SetLocation(loc);
	this->SetActorTransform(trans);
}

void AMasterNPC::RotateTowardsPlayer(AActor* iPlayer)
{
	FRotator playerRot = iPlayer->GetActorRotation();
	if (playerRot.Yaw < 0)
	{
		GetSprite()->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else
	{
		GetSprite()->SetRelativeRotation(FRotator(0, -180.0f, 0));
	}

}

void AMasterNPC::SetDataTableObjectDataRowNames()
{
	if (DataTableObjectData != nullptr)
	{
		DataTableObjectRowNames = DataTableObjectData->GetRowNames();
	}
}

void AMasterNPC::StartInitializeTimer()
{
	FTimerHandle MasterNPCInitializeTimer;
	GetWorld()->GetTimerManager().SetTimer(MasterNPCInitializeTimer, this, &AMasterNPC::InitializeDelayed,
		initializeTimer, false);
}

void AMasterNPC::InitializeDelayed()
{
	InitializeDataTableInfo();
	PassDataFromTableToObjectVariables();
}

void AMasterNPC::InitializeDataTableInfo()
{
	FNPCData* npcData = DataTableObjectData->FindRow<FNPCData>(
		DataTableObjectRowNames[DTNPCDataRowNumber], "MasterNPC ObjectData", true);
	if (npcData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("npcData LOADED SUCCESSFULLY."));
		currentNPCDialogues = npcData->npcDialogues;
		currentNPCStats = npcData->npcStats;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("npcData load FAILED"));
	}
}

void AMasterNPC::InitializeReferences()
{

	refDialogueSelectionMenu = CastChecked<UDialogueSelectionMenu>(dialogueSelectionComp->GetUserWidgetObject());
	refDialogueSelectionMenu->refOwnerNPC = this; 
}

void AMasterNPC::PassDataFromTableToObjectVariables()
{

}

void AMasterNPC::ShowNextDialogueMessage()
{


	if (refDialogueSelectionMenu == nullptr || refDialogueSelectionMenu->refDialogueTextWidget == nullptr)
	{
		return;
	}

	//check if arrays are valid
	if (!(currentNPCDialogues.dialogueMessages.IsValidIndex(0) &&
		currentNPCDialogues.dialogueMessagesRumor.IsValidIndex(0)))
	{
		return;
	}

	//if dialogue loops, it just gets to the end and starts again, can also make random later so it shows rand message
	//if not, when it gets to the end just keep showing message ...
	if (bDoesDialogueLoop)
	{
		GreetingsLoopMessage();
	}
	else
	{
		if (!bIsDialogueExhausted)
		{
			GreetingsNonLoopMessage();

		}
		else
		{
			//check if player has done any of the events
			if (bHasPlayerDoneEvent1 || bHasPlayerDoneEvent2 || bHasPlayerDoneEvent3 || bHasPlayerDoneEvent4)
			{
				if (bHasPlayerDoneEvent1 && !bEvent1DialogueFinished)
				{
					if (!currentNPCDialogues.dialogueMessagesHasDoneEvent1.IsValidIndex(0))
					{
						return;	//checking this just in case i might accidentally delete a row in Datatable
					}
					Event1Dialogue();
					return;
				}
				else if (bHasPlayerDoneEvent2 && !bEvent2DialogueFinished)
				{
					if (!currentNPCDialogues.dialogueMessagesHasDoneEvent2.IsValidIndex(0))
					{
						return; //checking this just in case i might accidentally delete a row in Datatable
					}
					Event2Dialogue();
					return;
				}
				else if (bHasPlayerDoneEvent3 && !bEvent3DialogueFinished)
				{
					if (!currentNPCDialogues.dialogueMessagesHasDoneEvent3.IsValidIndex(0))
					{
						return;//checking this just in case i might accidentally delete a row in Datatable
					}
					Event3Dialogue();
					return;
				}
				else if (bHasPlayerDoneEvent4 && !bEvent4DialogueFinished)
				{
					if (!currentNPCDialogues.dialogueMessagesHasDoneEvent4.IsValidIndex(0))
					{
						return;//checking this just in case i might accidentally delete a row in Datatable
					}
					Event4Dialogue();
					return;
				}
			}
			else
			{
				ExhaustedDialogue();
			}
			ExhaustedDialogue();
		
			if (bHasPlayerDoneEvent4 && bHasPlayerDoneEvent3 && bHasPlayerDoneEvent2 && bHasPlayerDoneEvent1)
			{
				AllEventsFinishedDialogue();
			}
		}
	}

}

void AMasterNPC::SetDialogueSelectInvisible()
{
	refDialogueSelectionMenu->SetVisibility(ESlateVisibility::Hidden);
}

void AMasterNPC::SetDialogueSelectVisible()
{
	refDialogueSelectionMenu->SetVisibility(ESlateVisibility::Visible);
}


void AMasterNPC::GreetingsLoopMessage()
{
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(currentNPCDialogues.dialogueMessages[simpleDialogueCounter]);
	if ((currentNPCDialogues.dialogueMessages.Num()) == simpleDialogueCounter)
	{
		simpleDialogueCounter = 0;
	}
	simpleDialogueCounter++;
}

void AMasterNPC::GreetingsNonLoopMessage()
{
	if ((currentNPCDialogues.dialogueMessages.Num()) == simpleDialogueCounter)
	{
		bIsDialogueExhausted = true;
		ExhaustedDialogue();
		return;
	}

	//not exhausted
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(currentNPCDialogues.dialogueMessages[simpleDialogueCounter]);
	simpleDialogueCounter++;
}

void AMasterNPC::ExhaustedDialogue()
{
	int32 l_randDialogue = FMath::RandRange(0, currentNPCDialogues.dialogueMessagesRumor.Num() - 1);
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesRumor[l_randDialogue]);
}

void AMasterNPC::Event1Dialogue()
{

	if ((currentNPCDialogues.dialogueMessagesHasDoneEvent1.Num()) == simpleDialogueCounterEvent1)
	{
		bEvent1DialogueFinished = true;
		ShowNextDialogueMessage();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("inside Event1 %i"), currentNPCDialogues.dialogueMessagesHasDoneEvent1.Num());
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesHasDoneEvent1[simpleDialogueCounterEvent1]);
	simpleDialogueCounterEvent1++;
}

void AMasterNPC::Event2Dialogue()
{
	if ((currentNPCDialogues.dialogueMessagesHasDoneEvent2.Num()) == simpleDialogueCounterEvent2)
	{
		bEvent2DialogueFinished = true;
		ShowNextDialogueMessage();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("inside Event2 %i"), currentNPCDialogues.dialogueMessagesHasDoneEvent2.Num());
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesHasDoneEvent2[simpleDialogueCounterEvent2]);
	simpleDialogueCounterEvent2++;
}

void AMasterNPC::Event3Dialogue()
{
	if ((currentNPCDialogues.dialogueMessagesHasDoneEvent3.Num()) == simpleDialogueCounterEvent3)
	{
		bEvent3DialogueFinished = true;
		ShowNextDialogueMessage();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("inside Event3 %i"), currentNPCDialogues.dialogueMessagesHasDoneEvent3.Num());
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesHasDoneEvent3[simpleDialogueCounterEvent3]);
	simpleDialogueCounterEvent3++;
}

void AMasterNPC::Event4Dialogue()
{
	if ((currentNPCDialogues.dialogueMessagesHasDoneEvent4.Num()) == simpleDialogueCounterEvent4)
	{
		bEvent4DialogueFinished = true;
		ShowNextDialogueMessage();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("inside Event4 %i"), currentNPCDialogues.dialogueMessagesHasDoneEvent4.Num());
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesHasDoneEvent4[simpleDialogueCounterEvent4]);
	simpleDialogueCounterEvent4++;
}

void AMasterNPC::AllEventsFinishedDialogue()
{
	int32 l_randDialogue = FMath::RandRange(0, currentNPCDialogues.dialogueMessagesPlayerHasDoneAllTasks.Num() - 1);
	refDialogueSelectionMenu->refDialogueTextWidget->refDialogueTextBlock->SetText(
		currentNPCDialogues.dialogueMessagesPlayerHasDoneAllTasks[l_randDialogue]);
}

void AMasterNPC::CreateDialogueSelection()
{
	if (refDialogueSelectionMenu == nullptr) { return; }
	refDialogueSelectionMenu->CreateDialogueButtons(currentNPCDialogues.dialogueSelectionMenuButtons);

}

void AMasterNPC::AddsMasterNPCRefToPlayer(AActor* iPlayer)
{
	ATGCharacter* playerChar = Cast<ATGCharacter>(iPlayer);
	if (playerChar != nullptr)
	{
		playerChar->refCurrentlyInteractingNPC = this;
	}
}
