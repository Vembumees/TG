// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBorder* refBorderSingleSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotDownLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotDownRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotUpLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlotUpRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UImage* refItemBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UImage* refItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USizeBox* refSizeBoxSlotSize;


protected:
	virtual void NativeConstruct() override;

};
