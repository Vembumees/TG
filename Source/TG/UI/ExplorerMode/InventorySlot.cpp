// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Components/SizeBox.h"

void UInventorySlot::UpdateInventoryButtonBackgroundType()
{

	FSlateBrush brush;
	
	//also randomly selects a random number which picks which image to have, so our slots look a bit different
	if (slotData.bIsSelected)
	{
		//is selected
		if (!bHasAlreadySetButtonBackground)
		{
			randVal = FMath::RandRange(0, 3);
			bHasAlreadySetButtonBackground = true;
		}

		switch (randVal)
		{
		case 0:
			brush.SetResourceObject(itemBackgroundSelected);
			break;
		case 1:
			brush.SetResourceObject(itemBackgroundSelected2);

			break;
		case 2:
			brush.SetResourceObject(itemBackgroundSelected3);

			break;
		case 3:
			brush.SetResourceObject(itemBackgroundSelected4);			

			break;
		}	

		refWBorderSingleSlot->SetBrush(brush);
	}
	else
	{
		//normal

		switch (randVal)
		{
		case 0:
			brush.SetResourceObject(itemBackgroundNormal);
			
			break;
		case 1:
			brush.SetResourceObject(itemBackgroundNormal2);

			break;
		case 2:
			brush.SetResourceObject(itemBackgroundNormal3);

			break;
		case 3:
			brush.SetResourceObject(itemBackgroundNormal4);

			break;
		}

		refWBorderSingleSlot->SetBrush(brush);
	}
}



void UInventorySlot::UpdateInventoryButtonBackgroundImage()
{
	FSlateBrush brush;
	switch (slotData.slotType)
	{
	case ESlotType::NORMAL:
		
				
		break;
	case ESlotType::ARTIFACT:

		brush.SetResourceObject(itemBackgroundImgArtifact);
		brush.SetImageSize(FVector2D(50, 50));
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
