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
		bIsArtifactSlot = false;
		inventorySlotState = EInventorySlotState::EMPTY;
		refItem = nullptr;
	}

	UPROPERTY(EditAnywhere)
		EInventoryType slotType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		bool bIsSelected;
	UPROPERTY(EditAnywhere)
		bool bIsArtifactSlot;
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
		class UBorder* refBorderSingleSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refButtonSlot;	//slot icon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemBackground; //this is the item background, can use for rarity
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refItemIcon;		// item icon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USizeBox* refSizeBoxSlotSize;

	FInventorySlotData slotData;

	//temp fix, dnt forget to update these in bp
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundNormal;
	UPROPERTY(EditAnywhere)
	class UPaperSprite* itemBackgroundSelected;

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

};
