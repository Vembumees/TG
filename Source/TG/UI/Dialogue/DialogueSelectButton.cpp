// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TG/UI/Dialogue/DialogueSelectionMenu.h"
#include "TG/UI/Dialogue/DialogueWidget.h"
#include "TG/NPCs/MasterNPC.h"

void UDialogueSelectButton::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}

void UDialogueSelectButton::ButtonPressedTalk()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedTalk()"));
	if (refOwnerNPC == nullptr)	{ return; }
	ClearPreviousDialogueWidgets();

	 	refOwnerNPC->refDialogueSelectionMenu->refDialogueTextWidget->SetVisibility(ESlateVisibility::Visible);
	 	refOwnerNPC->ShowNextDialogueMessage();	
		GetWorld()->GetTimerManager().SetTimer(
			hideDialogueTextWindowTimer, this, &UDialogueSelectButton::HideDialogueText, 5.0f, false);
}

void UDialogueSelectButton::ButtonPressedAsk()
{
	if (refOwnerNPC == nullptr) { return; }
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedAsk()"));
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedGive()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedGive()"));
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedTrade()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedTrade()"));
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedInvite()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedInvite()"));
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedDuel()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedDuel()"));
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ButtonPressedDuelPractice()
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::ButtonPressedDuelPractice()"));
	if (refOwnerNPC == nullptr) { return; }
	ClearPreviousDialogueWidgets();
}

void UDialogueSelectButton::ClearPreviousDialogueWidgets()
{
	//TODO: here clear other button's tabs !!
}

void UDialogueSelectButton::HideDialogueText()
{
	//this would need an animation in future
	refOwnerNPC->refDialogueSelectionMenu->refDialogueTextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueSelectButton::SetButtonText(EDialogueSelectButtons iBtn, const int32 iIdx)
{
	int32 idx = iIdx;
	idx += 1;
	FString l_text;
	switch (iBtn)
	{
	case EDialogueSelectButtons::TALK:
		l_text.AppendInt(idx);
		l_text.Append(" to Talk");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::ASK:
		l_text.AppendInt(idx);
		l_text.Append(" to Ask");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::GIVE:
		l_text.AppendInt(idx);
		l_text.Append(" to Give");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::TRADE:
		l_text.AppendInt(idx);
		l_text.Append(" to Trade");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::INVITE:
		l_text.AppendInt(idx);
		l_text.Append(" to Invite");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::DUEL:
		l_text.AppendInt(idx);
		l_text.Append(" to Duel");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
		break;
	case EDialogueSelectButtons::DUELPRACTICE:
		l_text.AppendInt(idx);
		l_text.Append(" to DuelPractice");
		refTextOnDialogueBtn->SetText(FText::FromString(l_text));
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

void UDialogueSelectButton::CallButtonFunctionWithInput(EDialogueSelectButtons iSelectedButton)
{
	//there already is a nullptr check stoping this from happening, but just in case
	if (!CheckIfHasSelectedButton(iSelectedButton))
	{
		UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectButton::CallButtonFunctionWithInput() failed, NPC doesnt have the selected option."));
		return;
	}
	switch (iSelectedButton)
	{
	case EDialogueSelectButtons::TALK:
		ButtonPressedTalk();
		break;
	case EDialogueSelectButtons::ASK:
		ButtonPressedAsk();
		break;
	case EDialogueSelectButtons::GIVE:
		ButtonPressedGive();
		break;
	case EDialogueSelectButtons::TRADE:
		ButtonPressedTrade();
		break;
	case EDialogueSelectButtons::INVITE:
		ButtonPressedInvite();
		break;
	case EDialogueSelectButtons::DUEL:
		ButtonPressedDuel();
		break;
	case EDialogueSelectButtons::DUELPRACTICE:
		ButtonPressedDuelPractice();
		break;
	}
}

bool UDialogueSelectButton::CheckIfHasSelectedButton(EDialogueSelectButtons iSelectedButton)
{
	for (auto& e : refOwnerNPC->refDialogueSelectionMenu->GetCurrentDialogueButtons())
	{
		if (e == iSelectedButton)
		{
			return true;
		}
	}
	return false;
}
