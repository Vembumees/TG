// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlotData
{
	GENERATED_BODY()

		FInventorySlotData()
	{
		slotType = EInventoryType::BAG;
		slotIndex = 0;
		bIsSelected = false;
	}

	UPROPERTY(EditAnywhere)
		EInventoryType slotType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		bool bIsSelected;

};


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
		class UButton* refButtonSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USizeBox* refSizeBoxSlotSize;

	FInventorySlotData slotData;

	//temp fix, dnt forget to update these in bp
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundNormal;
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundSelected;
	
	void UpdateInventoryButtonBackgroundType();



protected:
	virtual void NativeConstruct() override;


	virtual void NativePreConstruct() override;

};
