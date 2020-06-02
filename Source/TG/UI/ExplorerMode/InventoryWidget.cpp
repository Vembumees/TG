// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySlot.h"
#include "TG/Libraries/InventoryLibrary.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "TG/Controllers/ExploreController.h"
#include "TG/TGCharacter.h"
#include "TG/Components/InventoryComponent.h"
#include "PaperSprite.h"
#include "TG/Components/AbilityComponent.h"
#include "Components/BoxComponent.h"
#include "TG/StaticLibrary.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	InitializeRefs();
	AddDelegateBindings();
	GetStartingSlot();




	FTimerHandle invWidgetInitializeWithTimer;
	GetWorld()->GetTimerManager().SetTimer(invWidgetInitializeWithTimer, this, &UInventoryWidget::InitializeWithTimer, 0.5f, false);


}

void UInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	InitializeRefsInBP();
	FTimerHandle dsa;
	GetWorld()->GetTimerManager().SetTimer(dsa, this, &UInventoryWidget::CreateInventorySlots, 0.3f, false);
}

void UInventoryWidget::CreateInventorySlots()
{
	if (refInventoryGridPanel == nullptr || refPlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::CreateInventorySlots() refInventoryGridPanel == nullptr"));
		return;
	}
	TArray<UInventorySlot*> slotOld = refPlayerCharacter->GetInventoryComponent()->refItemInventory;
	int32 l_column = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns;
	int32 l_rows = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows;
	int32 l_nrOfSlots = (l_rows * l_column) - 1;
	mapRefInventorySlots.Empty();
	refPlayerCharacter->GetInventoryComponent()->refItemInventory.Empty();
	refInventoryGridPanel->ClearChildren();
	invSize = UInventoryLibrary::GetInventorySlotSize(EInventoryType::BAG);
	for (int i = 0; i <= l_nrOfSlots; i++)
	{
		//dont forget to update the class in WBP with the BP one
		UInventorySlot* wInvSlot = CreateWidget<UInventorySlot>(GetWorld(), invSlotClass);
		int32 l_currColumn = i / l_column;
		int32 l_currRow = i - ((i / l_column) * l_column);
		refInventoryGridPanel->AddChildToUniformGrid(wInvSlot,
			l_currColumn, l_currRow);
		mapRefInventorySlots.Add(FVector2D(l_currColumn, l_currRow), wInvSlot);
		wInvSlot->slotData.inventorySlotState = EInventorySlotState::EMPTY;
		if (slotOld.IsValidIndex(1))
		{
			if (slotOld[i]->slotData.inventorySlotState == EInventorySlotState::EMPTY)
			{
				wInvSlot->slotData.inventorySlotState = EInventorySlotState::EMPTY;
				wInvSlot->slotData.refItem = nullptr;
			}
			else
			{
				wInvSlot->slotData.inventorySlotState = EInventorySlotState::HASITEM;
				wInvSlot->slotData.refItem = slotOld[i]->slotData.refItem;
			}
		}
		
		//artifact slots 9-11, 16-18 with current layout (3x7)
		if ((i > 8 && i < 12) || (i > 15 && i < 19))
		{
			wInvSlot->slotData.bIsArtifactSlot = true;
			wInvSlot->UpdateInventoryButtonBackgroundImage();
		}
		
		wInvSlot->slotData.slotIndex = i;
		wInvSlot->slotData.slotType = EInventoryType::BAG;
		wInvSlot->refSizeBoxSlotSize->SetWidthOverride(invSize);
		wInvSlot->refSizeBoxSlotSize->SetHeightOverride(invSize);

		
		//add inventory slot reference to the player's inventory component
		refPlayerCharacter->GetInventoryComponent()->refItemInventory.Add(wInvSlot);
		
	}

	HighlightSelectedSlot();
}

void UInventoryWidget::InitializeWithTimer()
{
	UpdateTooltipData();
}

void UInventoryWidget::AddDelegateBindings()
{
	refExplorePlayerController = Cast<AExploreController>(GetWorld()->GetFirstPlayerController());
	refExplorePlayerController->delegateInventoryMove.AddDynamic(this, &UInventoryWidget::MoveInInventory);
	//this is initialized with InitializeRefs, which at least atm is called before this so its safe
	refPlayerCharacter->GetInventoryComponent()->delegateInventoryUpdate.AddDynamic(this, &UInventoryWidget::UpdateItemsFromPlayerInventory);
	refExplorePlayerController->delegateInventoryUseItem.AddDynamic(this, &UInventoryWidget::UseSelectedItem);
	refExplorePlayerController->delegateInventoryDropItem.AddDynamic(this, &UInventoryWidget::DropSelectedItem);

}

void UInventoryWidget::InitializeRefs()
{
	//init player pawn ref
	refPlayerCharacter = Cast<ATGCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UInventoryWidget::MoveInInventory(EMoveDirections iMoveDir)
{
	FVector2D l_targetDirection = currentlyActiveSlot;
	switch (iMoveDir)
	{
	case EMoveDirections::UP:
		UE_LOG(LogTemp, Warning, TEXT("UP"));
		l_targetDirection.X -= 1;
		break;
	case EMoveDirections::DOWN:
		l_targetDirection.X += 1;
		UE_LOG(LogTemp, Warning, TEXT("DOWN"));
		break;
	case EMoveDirections::LEFT:
		l_targetDirection.Y -= 1;
		UE_LOG(LogTemp, Warning, TEXT("LEFT"));
		break;
	case EMoveDirections::RIGHT:
		l_targetDirection.Y += 1;
		UE_LOG(LogTemp, Warning, TEXT("RIGHT"));
		break;
	}
	if (mapRefInventorySlots.Find(l_targetDirection))
	{
		SelectNeighbourSlot(l_targetDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("direction where I wanted to move was invalid."));
	}

}

void UInventoryWidget::HighlightSelectedSlot()
{
	UInventorySlot* l_ref = *mapRefInventorySlots.Find(currentlyActiveSlot);
	l_ref->slotData.bIsSelected = true;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UInventoryWidget::DeHighlightLastSelectedSlot()
{
	UInventorySlot* l_ref = *mapRefInventorySlots.Find(lastActiveSlot);
	l_ref->slotData.bIsSelected = false;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UInventoryWidget::SelectNeighbourSlot(FVector2D iTarget)
{
	lastActiveSlot = currentlyActiveSlot;
	currentlyActiveSlot = iTarget;
	DeHighlightLastSelectedSlot();
	HighlightSelectedSlot();
	UpdateTooltipData();
}

void UInventoryWidget::GetStartingSlot()
{
	//makes the selection start somewhere from the middle, not really accurate and well thought out, good enough
// 	float l_column = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns;
// 	float l_rows = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows;
// 	l_column = FMath::RoundHalfToEven(l_column / 2);
// 	l_rows = FMath::RoundHalfToEven(l_rows / 2);
// 
// 	//this is just so that with 3x3 selection would be in the middle, there's probably a proper math formula for this
// 	l_column -= 1;
// 	l_rows -= 1;
// 
// 	//clamp it so it doesnt go over the column/row sizes, this function needs const parameters so making temp consts
// 	const int32 l_tmpClmn = l_column;
// 	const int32 l_tmpRows = l_rows;
// 	l_column = FMath::Clamp(l_tmpClmn, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns);
// 	l_rows = FMath::Clamp(l_tmpRows, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows);
// 	FVector2D midVec = FVector2D(l_column, l_rows);
// 	currentlyActiveSlot = midVec; //replace this
	

	//above stuff is attempt to make it start from middle but it breaks with certain sizes, fk it just starts in 0, simple
	currentlyActiveSlot = FVector2D(0,0);
}

void UInventoryWidget::UpdateItemsFromPlayerInventory(TArray<class UInventorySlot*> iPlayerInventory)
{
	UE_LOG(LogTemp, Warning, TEXT(" UInventoryWidget::UpdateItemsFromPlayerInventory()"));
	TArray<UInventorySlot*> mapValues;
	mapRefInventorySlots.GenerateValueArray(mapValues);
	int32 loopCounter = 0;
	for (auto& e : iPlayerInventory)
	{
		if (e->slotData.inventorySlotState == EInventorySlotState::HASITEM)
		{
			FSlateBrush brush;
			brush.SetResourceObject(e->slotData.refItem->currentItemData.itemIcon);
			//update icon
			mapValues[loopCounter]->refItemIcon->SetBrush(brush);
			mapValues[loopCounter]->refItemIcon->SetBrushSize(FVector2D(45, 45));

			//add item pointer
			mapValues[loopCounter]->slotData.refItem = e->slotData.refItem;
		}
		loopCounter++;
	}
}

void UInventoryWidget::UpdateTooltipData()
{


	//lets find the selected slot data
	UInventorySlot* l_currInventorySlot = *mapRefInventorySlots.Find(currentlyActiveSlot);
	if (l_currInventorySlot == nullptr)
	{
		refTooltipBox->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	if (l_currInventorySlot->slotData.inventorySlotState == EInventorySlotState::EMPTY)
	{
		refTooltipBox->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot->slotData.refItem == nullptr"));
		return;
	}

	FItemData l_selectedItemData = l_currInventorySlot->slotData.refItem->currentItemData;



	//update refTextItemName
	refTextItemName->SetText(l_selectedItemData.itemName);
	//update refTextItemRarity && update refBorderName, border color
	switch (l_selectedItemData.itemRarity)
	{
	case EItemRarity::COMMON:
		refBorderName->SetBrushColor(FLinearColor::Gray); //hardcode color
		refTextItemRarity->SetText(FText::FromString("Common"));
		break;
	case EItemRarity::MAGIC:
		refBorderName->SetBrushColor(FLinearColor::Blue); //hardcode color
		refTextItemRarity->SetText(FText::FromString("Magic"));
		break;
	case EItemRarity::ULTRA:
		refBorderName->SetBrushColor(FLinearColor::Green); //hardcode color
		refTextItemRarity->SetText(FText::FromString("UltrA"));
		break;
	}

	//update refTExtItemType
	switch (l_selectedItemData.itemType)
	{
	case EItemType::TOME:
		refTextItemType->SetText(FText::FromString("tome"));
		break;
	case EItemType::TOKEN:
		refTextItemType->SetText(FText::FromString("token"));
		break;
	case EItemType::SOUL:
		refTextItemType->SetText(FText::FromString("soul"));
		break;
	case EItemType::MYSTICAL:
		refTextItemType->SetText(FText::FromString("mystical"));
		break;
	}
	//update refTextItemDescription
	refTextItemDescription->SetText(FText::FromString(l_selectedItemData.itemDescription));

	refTooltipBox->SetVisibility(ESlateVisibility::Visible);

	//update refVerticalBoxItemEffects, here we add a child of another widget we create later TODO !!

}

void UInventoryWidget::UseSelectedItem()
{
	//lets find the selected slot data
	if (!mapRefInventorySlots.Contains(currentlyActiveSlot))
	{
		return;
	}
	UInventorySlot* l_currInventorySlot = *mapRefInventorySlots.Find(currentlyActiveSlot);

	UE_LOG(LogTemp, Warning, TEXT("\n SLOTDATA \n Index: %i \n ArtifactSlot: %i \n slotType: %s"),
		l_currInventorySlot->slotData.slotIndex,
		l_currInventorySlot->slotData.bIsArtifactSlot,
		*UStaticLibrary::GetEnumValueAsString("EInventoryType", l_currInventorySlot->slotData.slotType)
		);

	refPlayerCharacter->GetAbilityComponent()->CastAbility(l_currInventorySlot->slotData.slotIndex);

}

void UInventoryWidget::DropSelectedItem()
{
	if (!mapRefInventorySlots.Contains(currentlyActiveSlot))
	{
		return;
	}
	UInventorySlot* l_currInventorySlot = *mapRefInventorySlots.Find(currentlyActiveSlot);
	if (l_currInventorySlot == nullptr || l_currInventorySlot->slotData.refItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	FVector playerLoc = refPlayerCharacter->GetActorLocation();
	if (refPlayerCharacter->bIsFacingRight)
	{
		playerLoc.X += 100;
	}
	else
	{
		playerLoc.X -= 100;
	}

	//current problem, i want the slot to stay empty until its filled with a new item, not the inventory to be reordered
	//hmm, for that I think I need to keep the player character array filled with entries and check if the entry slot is empty or has item

	l_currInventorySlot->slotData.refItem->SetActorLocation(playerLoc, true);
	l_currInventorySlot->slotData.refItem->SetActorHiddenInGame(false);
	l_currInventorySlot->slotData.refItem->GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	refPlayerCharacter->GetInventoryComponent()->DeleteItemFromInventory(l_currInventorySlot->slotData.slotIndex);
	CreateInventorySlots();
	UpdateItemsFromPlayerInventory(refPlayerCharacter->GetInventoryComponent()->GetItemInventory());

}

int32 UInventoryWidget::GetFirstEmptyInventorySlotIndex()
{
	TArray<UInventorySlot*> mapValues;
	mapRefInventorySlots.GenerateValueArray(mapValues);
	for (auto& e : mapValues)
	{
		if (e->slotData.inventorySlotState == EInventorySlotState::EMPTY)
		{
			return e->slotData.slotIndex;
		}
	}
	//inventory apparently is full
	return -1;

}





