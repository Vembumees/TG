// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuSlot.generated.h"


USTRUCT(BlueprintType)
struct FMenuSlotData
{
	GENERATED_BODY()

		FMenuSlotData()
	{
		menuType = EMenuType::MAINMENU;
		slotIndex = 0;
		bIsSelected = false;

	}

	UPROPERTY(EditAnywhere)
		EMenuType menuType;
	UPROPERTY(EditAnywhere)
		int32 slotIndex;
	UPROPERTY(EditAnywhere)
		bool bIsSelected;

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

	FMenuSlotData menuSlotData;

	//temp fix, dnt forget to update these in bp
	UPROPERTY(EditAnywhere)
		class UTexture2D* iconBackground;

	UPROPERTY(EditAnywhere)
		FLinearColor imgColorSelected;
	UPROPERTY(EditAnywhere)
		FLinearColor imgColorNormal;

	void UpdateInventoryButtonBackgroundType();

protected:

	virtual void NativeConstruct() override;



};
