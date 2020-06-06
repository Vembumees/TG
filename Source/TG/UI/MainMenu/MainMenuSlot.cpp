// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "MenuItem.h"
#include "PaperSprite.h"

void UMainMenuSlot::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	UpdateInventoryButtonBackgroundType();
	SetSlotSize();
}

void UMainMenuSlot::UpdateInventoryButtonBackgroundType()
{
	//In menu slot we want to make the icon to go from grayish to colorful and maybe play rotate animation
	FSlateBrush brush;
	if (menuSlotData.bIsSelected)
	{
		//is selected
		brush.TintColor = imgColorSelected;
		brush.SetResourceObject(menuIconBackgroundSlotTextures.itemBackgroundSelected);
	}
	else
	{
		//normal
		brush.TintColor = imgColorNormal;
		brush.SetResourceObject(menuIconBackgroundSlotTextures.itemBackgroundNormal);
	}

	refWBorderSingleSlot->SetBrush(brush);
}

void UMainMenuSlot::SetSlotSize()
{
	refWSizeBoxSlotSize->SetHeightOverride(100);
	refWSizeBoxSlotSize->SetWidthOverride(100);
}
