// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridPanel.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UInventoryGridPanel : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUniformGridPanel* refGridPanelUniformGridPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UInventorySlot* refInventorySlot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UInventorySlot*> refInventorySlots;



protected:
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;


	virtual void NativeConstruct() override;


};
