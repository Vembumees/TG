// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueSelectionMenu.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UDialogueSelectionMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeRefsInBP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHorizontalBox* refDialogueMenuHorizontalBox;

protected:
	virtual void NativeConstruct() override;

	

};
