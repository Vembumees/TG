// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExplorerModeScreen.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UExplorerModeScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeReferencesInBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UInventoryWidget* refInventoryWidget;
protected:
	virtual void NativeConstruct() override;

};
