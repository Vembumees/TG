// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Components/SizeBox.h"

void UInventorySlot::UpdateInventoryButtonBackgroundType()
{

	FSlateBrush brush;

	if (slotData.bIsSelected)
	{
		//is selected
		brush.SetResourceObject(itemBackgroundSelected);
		refBorderSingleSlot->SetBrush(brush);
	}
	else
	{
		//normal
		brush.SetResourceObject(itemBackgroundNormal);
		refBorderSingleSlot->SetBrush(brush);
	}
}



void UInventorySlot::UpdateInventoryButtonBackgroundImage()
{
	FSlateBrush brush;
	if (slotData.bIsArtifactSlot)
	{
	  //is artifact
		brush.SetResourceObject(itemBackgroundImgArtifact);
		brush.SetImageSize(FVector2D(55, 55));
		refItemBackground->SetColorAndOpacity(imgBackgroundColorARTIFACT);
	}
	else
	{
		//normal
		brush.SetResourceObject(itemBackgroundImgNormal);
		brush.SetImageSize(FVector2D(42, 42));
		refItemBackground->SetColorAndOpacity(imgBackgroundColorNormal);
	}

	
	refItemBackground->SetBrush(brush);
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	UpdateInventoryButtonBackgroundType();
	UpdateInventoryButtonBackgroundImage();
}

void UInventorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	InitializeRefsInBP();
}
