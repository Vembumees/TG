// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterNPC.h"
#include "TG/TG.h"
#include "PaperFlipbookComponent.h"
#include "Components/WidgetComponent.h"
#include "TG/UI/Dialogue/DialogueWidget.h"
#include "Components/TextBlock.h"

AMasterNPC::AMasterNPC()
{
	dialogueAlert= CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("dialogueAlert"));
	dialogueAlert->SetupAttachment(RootComponent);
	dialogueAlert->SetRelativeLocation(FVector(30,0,150));
	dialogueAlert->SetRelativeScale3D(FVector(3,3,3));
	dialogueAlert->SetVisibility(false);

	//sets our character sprite default scale
	GetSprite()->SetRelativeScale3D(TG_SPRITE_SCALE);

	dialogueComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("dialogueComp"));
	dialogueComp->SetupAttachment(RootComponent);
	dialogueComp->SetRelativeLocation(FVector(30, 0, 150));
	dialogueComp->SetVisibility(true);
	dialogueComp->SetCollisionProfileName(TEXT("NoCollision"));
	dialogueComp->SetGenerateOverlapEvents(false);
	dialogueComp->SetWidgetSpace(EWidgetSpace::Screen);


	/* ###########################################################
						default values
	 ########################################################### */

	simpleDialogueCounter = 0;

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
	refDialogueWidget->SetVisibility(ESlateVisibility::Hidden);

}

void AMasterNPC::Interact(AActor* iPlayer)
{
	RotateTowardsPlayer(iPlayer);
	dialogueAlert->SetVisibility(false);
	refDialogueWidget->SetVisibility(ESlateVisibility::Visible);
	ShowNextDialogueMessage();
}

void AMasterNPC::BeginPlay()
{
	Super::BeginPlay();

	

	refDialogueWidget = CastChecked<UDialogueWidget>(dialogueComp->GetUserWidgetObject());
	refDialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	FNPCDialogues demo;
	demo.dialogueMessage = FText::FromString("Man I'd do anything for a cigarette right now.");
	FNPCDialogues demo2;
	demo2.dialogueMessage = FText::FromString("I really mean it dude, I'll blow you for a pack!");
	FNPCDialogues demo3;
	demo3.dialogueMessage = FText::FromString("I'll even swallow your load!");
	dialogueMessages.Add(demo);
	dialogueMessages.Add(demo2);
	dialogueMessages.Add(demo3);


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

void AMasterNPC::ShowNextDialogueMessage()
{
	if (refDialogueWidget == nullptr || refDialogueWidget->refDialogueTextBlock == nullptr)
	{
		return;
	}


	refDialogueWidget->refDialogueTextBlock->SetText(dialogueMessages[simpleDialogueCounter].dialogueMessage);
	simpleDialogueCounter++;
	if ((dialogueMessages.Num()) == simpleDialogueCounter)
	{
		simpleDialogueCounter = 0;
	}

}
