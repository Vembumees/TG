// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"

#include "TG/Item/Item.h"
#include "InventoryWidget.generated.h"


UCLASS()
class TG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

	/* ###########################################################
						ITEM SLOTS
	 ########################################################### */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UUniformGridPanel* refInventoryGridPanel;

	/* #########################END############################## */



	/* ###########################################################
						TOOLTIP
	 ########################################################### */

	 //the parent of the tooltip box, default hidden
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USizeBox* refTooltipBox;

	//border, this is used to change the name color based on the rarity or type of item
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBorder* refBorderName;

	//parent of the inventory grid panel
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refGridPanelBackgroundButton;

	//textblock, item name 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refTextItemName;

	//textblock, item rarity, magic, rare, unique etc
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refTextItemRarity;

	//textblock, item type, token, scroll, spell, gem, currency etc
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refTextItemType;

	//textBlock, item description
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refTextItemDescription;

	//textblock for item effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UVerticalBox* refVerticalBoxItemEffects;


	/* #########################END############################## */


	UPROPERTY(EditAnywhere)
		float invSize;

	UPROPERTY(EditAnywhere)
		TMap<FVector2D, class UInventorySlot*> mapRefInventorySlots;

	UPROPERTY()
		class ATGCharacter* refPlayerCharacter;
	UPROPERTY()
		class AExploreController* refExplorePlayerController;

protected:
	virtual void NativeConstruct() override;


	virtual void NativePreConstruct() override;

	UFUNCTION()
		void CreateInventorySlots();


	void InitializeWithTimer();
	void AddDelegateBindings();
	void InitializeRefs();
	

	UFUNCTION()
		void MoveInInventory(EMoveDirections iMoveDir);

	//dont forget to update the class in WBP with the BP one
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UInventorySlot> invSlotClass;

	//inventory selection what do i need to do
	//move up/down/left/right, add the selected img on selected one and normal one on last.

	FVector2D currentlyActiveSlotCoord;
	FVector2D lastActiveSlotCoord;

	int32 currentlySelectedItemForMoveIndex;
	FVector2D lastSelectedItemForMoveSlotCoord;

	//Making 2 of these instead of one function with inputs because i think this is a little bit easier to understand
	void HighlightSelectedSlot();
	void DeHighlightLastSelectedSlot();
	void SelectNeighbourSlot(FVector2D iTarget);
	void GetStartingSlot();

	UFUNCTION()
		void UpdateItemsFromPlayerInventory(TArray<class UInventorySlot*> iPlayerInventory);

	void UpdateTooltipData();


	UFUNCTION()
		void UseSelectedItem();

	UFUNCTION()
		void DropSelectedItem();

	UFUNCTION()
		void InventoryMoveActionSelectedItem();

	bool bAreWeDoingAMoveAction;
public:
	int32 GetFirstEmptyInventorySlotIndex();

	private:
		FLinearColor l_oldSlotColor;
};
