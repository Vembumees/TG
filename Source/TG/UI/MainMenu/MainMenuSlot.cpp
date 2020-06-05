// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"


void UMainMenuSlot::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	UpdateInventoryButtonBackgroundType();
	UpdateInventoryButtonBackgroundImage();
}

void UMainMenuSlot::UpdateInventoryButtonBackgroundType()
{
	//In menu slot we want to make the icon to go from grayish to colorful and maybe play rotate animation
	FSlateBrush brush;
	if (menuSlotData.bIsSelected)
	{
		//is selected
		brush.TintColor = imgColorSelected;
	}
	else
	{
		//normal
		brush.TintColor = imgColorNormal;
	}
	brush.SetResourceObject(iconBackground);
	refWBorderSingleSlot->SetBrush(brush);
}
