// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "MainMenuSlot.generated.h"


USTRUCT(BlueprintType)
struct FMenuSlotData
{
	GENERATED_BODY()

	FMenuSlotData()
	{
		menuType = EMenuType::MAINMENU;
		slotIndex = 0;
		slotCoords = FVector2D(0,0);
		bIsSelected = false;
		menuInventorySlotState = EInventorySlotState::EMPTY;
		refMenuItem = nullptr;
		
	}

	UPROPERTY(EditAnywhere)
		EMenuType menuType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		FVector2D slotCoords;
	UPROPERTY(EditAnywhere)
		bool bIsSelected;
	UPROPERTY(EditAnywhere)
		EInventorySlotState menuInventorySlotState;
	UPROPERTY(EditAnywhere)
		EInventoryVisibilityState menuInventorySlotVisibility;
	UPROPERTY(EditAnywhere)
		class AMenuItem* refMenuItem;

};


USTRUCT(BlueprintType)
struct FMenuIconBackgroundSlotTextures
{
	GENERATED_BODY()

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
};

UCLASS()
class TG_API UMainMenuSlot : public UUserWidget
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
		class USizeBox* refWSizeBoxSlotSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refSlotItemIcon;

	FMenuSlotData menuSlotData;
	
	UPROPERTY(EditAnywhere)
	FMenuIconBackgroundSlotTextures menuIconBackgroundSlotTextures;

	UPROPERTY(EditAnywhere)
		FLinearColor imgColorSelected;
	UPROPERTY(EditAnywhere)
		FLinearColor imgColorNormal;

	void UpdateInventoryButtonBackgroundType();
	void SetSlotSize();

protected:

	virtual void NativeConstruct() override;



};
