// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refDialogueTextBlock;
	

protected:

	
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeBPRefs();


	virtual void NativeConstruct() override;

};
