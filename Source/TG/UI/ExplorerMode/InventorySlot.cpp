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
		refWBorderSingleSlot->SetBrush(brush);
	}
	else
	{
		//normal
		brush.SetResourceObject(itemBackgroundNormal);
		refWBorderSingleSlot->SetBrush(brush);
	}
}



void UInventorySlot::UpdateInventoryButtonBackgroundImage()
{
	FSlateBrush brush;
	switch (slotData.slotType)
	{
	case ESlotType::NORMAL:

		brush.SetResourceObject(itemBackgroundImgNormal);
		brush.SetImageSize(FVector2D(42, 42));
		refWItemBackground->SetColorAndOpacity(imgBackgroundColorNormal);

		break;
	case ESlotType::ARTIFACT:

		brush.SetResourceObject(itemBackgroundImgArtifact);
		brush.SetImageSize(FVector2D(55, 55));
		refWItemBackground->SetColorAndOpacity(imgBackgroundColorARTIFACT);

		break;
	case ESlotType::SLOTTYPE2:
		break;
	case ESlotType::SLOTTYPE3:
		break;
	case ESlotType::SLOTTYPE4:
		break;
	case ESlotType::SLOTTYPE5:
		break;
	case ESlotType::SLOTTYPE6:
		break;
	default:
		break;
	}

	
	refWItemBackground->SetBrush(brush);
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
