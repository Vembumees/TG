// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBorder* refBorderSingleSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotDownLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotDownRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotUpLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotUpRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USizeBox* refSizeBoxSlotSize;


	UPROPERTY(EditAnywhere)
		EInventoryType slotType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		int32 dragNrFrame;


protected:
	virtual void NativeConstruct() override;


	virtual void NativePreConstruct() override;

};
