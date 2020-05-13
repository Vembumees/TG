// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TG/UI/Dialogue/DialogueWidget.h"
#include "TG/NPCs/MasterNPC.h"

void UDialogueSelectButton::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}

void UDialogueSelectButton::ButtonPressedTalk()
{
	if (refOwnerNPC == nullptr)	{ return; }
	ClearPreviousDialogueWidgets();

	 	refOwnerNPC->refDialogueTextWidget->SetVisibility(ESlateVisibility::Visible);
	 	refOwnerNPC->ShowNextDialogueMessage();	
}

void UDialogueSelectButton::ButtonPressedAsk()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedGive()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedTrade()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedInvite()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedDuel()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedDuelPractice()
{
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ClearPreviousDialogueWidgets()
{
	//TODO: here clear other button's tabs !!
}

void UDialogueSelectButton::SetButtonText(EDialogueSelectButtons iBtn)
{
	switch (iBtn)
	{
	case EDialogueSelectButtons::TALK:
		refTextOnDialogueBtn->SetText(FText::FromString("Talk"));
		break;
	case EDialogueSelectButtons::ASK:
		refTextOnDialogueBtn->SetText(FText::FromString("Ask"));
		break;
	case EDialogueSelectButtons::GIVE:
		refTextOnDialogueBtn->SetText(FText::FromString("Give"));
		break;
	case EDialogueSelectButtons::TRADE:
		refTextOnDialogueBtn->SetText(FText::FromString("Trade"));
		break;
	case EDialogueSelectButtons::INVITE:
		refTextOnDialogueBtn->SetText(FText::FromString("Invite"));
		break;
	case EDialogueSelectButtons::DUEL:
		refTextOnDialogueBtn->SetText(FText::FromString("Duel"));
		break;
	case EDialogueSelectButtons::DUELPRACTICE:
		refTextOnDialogueBtn->SetText(FText::FromString("DuelPractice"));
		break;
	}
}

void UDialogueSelectButton::SetButtonBinding(EDialogueSelectButtons iBtn)
{
	switch (iBtn)
	{
	case EDialogueSelectButtons::TALK:
		
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedTalk);
		break;
	case EDialogueSelectButtons::ASK:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedAsk);
		break;
	case EDialogueSelectButtons::GIVE:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedGive);
		break;
	case EDialogueSelectButtons::TRADE:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedTrade);
		break;
	case EDialogueSelectButtons::INVITE:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedInvite);
		break;
	case EDialogueSelectButtons::DUEL:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedDuel);
		break;
	case EDialogueSelectButtons::DUELPRACTICE:
		refButtonDialogue->OnClicked.AddDynamic(this, &UDialogueSelectButton::ButtonPressedDuelPractice);
		break;
	}
}
