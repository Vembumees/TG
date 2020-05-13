// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "DialogueSelectButton.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UDialogueSelectButton : public UUserWidget
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			class UButton* refButtonDialogue;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			class UTextBlock* refTextOnDialogueBtn;

		//index is to show what button to select it with
		void SetButtonText(EDialogueSelectButtons iBtn, const int32 iIdx);
		void SetButtonBinding(EDialogueSelectButtons iBtn);

		void CallButtonFunctionWithInput(EDialogueSelectButtons iSelectedButton);
		bool CheckIfHasSelectedButton(EDialogueSelectButtons iSelectedButton);
		class AMasterNPC* refOwnerNPC; // gets initialized in selectionmenu
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void ButtonPressedTalk();
	UFUNCTION()
	void ButtonPressedAsk();
	UFUNCTION()
	void ButtonPressedGive();
	UFUNCTION()
	void ButtonPressedTrade();
	UFUNCTION()
	void ButtonPressedInvite();
	UFUNCTION()
	void ButtonPressedDuel();
	UFUNCTION()
	void ButtonPressedDuelPractice();
	
	void ClearPreviousDialogueWidgets();
	void HideDialogueText();

	FTimerHandle hideDialogueTextWindowTimer;
	
};
