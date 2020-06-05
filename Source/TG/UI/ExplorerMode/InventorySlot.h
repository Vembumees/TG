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
		inventoryType = EInventoryType::BAG;
		slotType = ESlotType::NORMAL;
		slotIndex = 0;
		bIsSelected = false;
		inventorySlotState = EInventorySlotState::EMPTY;
		refItem = nullptr;
	}

	UPROPERTY(EditAnywhere)
		EInventoryType inventoryType;
	UPROPERTY(EditAnywhere)
		ESlotType slotType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		bool bIsSelected;
	UPROPERTY(EditAnywhere)
		EInventorySlotState inventorySlotState;
	UPROPERTY(EditAnywhere)
		class AItem* refItem;

};


UCLASS()
class TG_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBorder* refWBorderSingleSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refWButtonSlot;	//slot icon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refWItemBackground; //this is the item background, can use for rarity
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refWItemIcon;		// item icon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USizeBox* refWSizeBoxSlotSize;

	FInventorySlotData slotData;

	//temp fix, dnt forget to update these in bp
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundNormal;
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundSelected;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundNormal2;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundSelected2;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundNormal3;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundSelected3;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundNormal4;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemBackgroundSelected4;

	UPROPERTY(EditAnywhere)
		class UTexture2D* itemBackgroundImgNormal;
	UPROPERTY(EditAnywhere)
		class UTexture2D* itemBackgroundImgArtifact;

	UPROPERTY(EditAnywhere)
		FLinearColor imgBackgroundColorARTIFACT;
	UPROPERTY(EditAnywhere)
		FLinearColor imgBackgroundColorNormal;
	
	void UpdateInventoryButtonBackgroundType();

	void UpdateInventoryButtonBackgroundImage();



protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

private:
	int32 randVal = 0;
	bool bHasAlreadySetButtonBackground = false;;
};
