// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UDialogueSelectButton::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}

void UDialogueSelectButton::SetButtonText(EDialogueSelectButtons iBtn)
{
	switch (iBtn)
	{
	case EDialogueSelectButtons::TALK:
		refTextDialogueButton->SetText(FText::FromString("Talk"));
		break;
	case EDialogueSelectButtons::ASK:
		refTextDialogueButton->SetText(FText::FromString("Ask"));
		break;
	case EDialogueSelectButtons::GIVE:
		refTextDialogueButton->SetText(FText::FromString("Give"));
		break;
	case EDialogueSelectButtons::TRADE:
		refTextDialogueButton->SetText(FText::FromString("Trade"));
		break;
	case EDialogueSelectButtons::INVITE:
		refTextDialogueButton->SetText(FText::FromString("Invite"));
		break;
	case EDialogueSelectButtons::DUEL:
		refTextDialogueButton->SetText(FText::FromString("Duel"));
		break;
	case EDialogueSelectButtons::DUELPRACTICE:
		refTextDialogueButton->SetText(FText::FromString("DuelPractice"));
		break;
	}
}
