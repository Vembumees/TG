// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "InventoryWidget.generated.h"


UCLASS()
class TG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UUniformGridPanel* refInventoryGridPanel;	

	UPROPERTY(EditAnywhere)
	float invSize;

	UPROPERTY(EditAnywhere)
		TMap<FVector2D, class UInventorySlot*> mapRefInventorySlots;

protected:
	virtual void NativeConstruct() override;


	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CreateInventorySlots();

	void AddDelegateBindings();
	
	UFUNCTION()
	void MoveInInventory(EMoveDirections iMoveDir);

	//dont forget to update the class in WBP with the BP one
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UInventorySlot> invSlotClass; 

	//inventory selection what do i need to do
	//move up/down/left/right, add the selected img on selected one and normal one on last.
	
	FVector2D currentlyActiveSlot;
	FVector2D lastActiveSlot;

	//Making 2 of these instead of one function with inputs because i think this is a little bit easier to understand
	void HighlightSelectedSlot();
	void DeHighlightLastSelectedSlot();

	void SelectNeighbourSlot(FVector2D iTarget);
};
