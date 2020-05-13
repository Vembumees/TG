// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
			class UTextBlock* refTextDialogueButton;

protected:
	virtual void NativeConstruct() override;


};
