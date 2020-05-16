// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySlot.h"
#include "TG/Libraries/InventoryLibrary.h"
#include "TG/Libraries/AbilityFunctionLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "TG/Controllers/ExploreController.h"
#include "TG/TGCharacter.h"
#include "TG/Components/InventoryComponent.h"
#include "PaperSprite.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	InitializeRefs();
	AddDelegateBindings();
	GetStartingSlot();



// 	FTimerHandle invWidgetInitializeWithTimer;
// 	GetWorld()->GetTimerManager().SetTimer(invWidgetInitializeWithTimer, this, &UInventoryWidget::InitializeWithTimer, 0.5f, false);


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
	if (refInventoryGridPanel == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::CreateInventorySlots() refInventoryGridPanel == nullptr"));
		return;
	}
	int32 l_column = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns;
	int32 l_rows = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows;
	int32 l_nrOfSlots = (l_rows * l_column) - 1;
	mapRefInventorySlots.Empty();
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
		wInvSlot->slotData.slotIndex = i;
		wInvSlot->slotData.slotType = EInventoryType::BAG;
		wInvSlot->refSizeBoxSlotSize->SetWidthOverride(invSize);
		wInvSlot->refSizeBoxSlotSize->SetHeightOverride(invSize);
	}
	
	HighlightSelectedSlot();
}

void UInventoryWidget::InitializeWithTimer()
{

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
	float l_column = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns;
	float l_rows = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows;
		l_column = FMath::RoundHalfToEven(l_column / 2);
		l_rows = FMath::RoundHalfToEven(l_rows / 2);
	
		//this is just so that with 3x3 selection would be in the middle, there's probably a proper math formula for this
		l_column -= 1; 
		l_rows	 -= 1;

		//clamp it so it doesnt go over the column/row sizes, this function needs const parameters so making temp consts
		const int32 l_tmpClmn = l_column;
		const int32 l_tmpRows = l_rows;				
		l_column = FMath::Clamp(l_tmpClmn, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns);
		l_rows = FMath::Clamp(l_tmpRows, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows);
	FVector2D midVec = FVector2D(l_column, l_rows);
	currentlyActiveSlot = midVec; //replace this
}

void UInventoryWidget::UpdateItemsFromPlayerInventory(TArray<class AItem*> iPlayerInventory)
{
	UE_LOG(LogTemp, Warning, TEXT(" UInventoryWidget::UpdateItemsFromPlayerInventory()"));
	TArray<UInventorySlot*> value;
	mapRefInventorySlots.GenerateValueArray(value);
	int32 loopCounter = 0;
	for (auto& e : iPlayerInventory)
	{
		FSlateBrush brush;
		brush.SetResourceObject(e->GetCurrentItemData().itemIcon);
		for (int i = loopCounter; i <= iPlayerInventory.Num() - 1; i++)
		{
			//update icon
			value[i]->refItemIcon->SetBrush(brush);
			value[i]->refItemIcon->SetBrushSize(FVector2D(45, 45));

			//add item pointer
			value[i]->slotData.refItem = e;
		}
		loopCounter++;
	}
}

void UInventoryWidget::UpdateTooltipData()
{
	/*tooltip, so what do i need to implement?
		tooltip should be visible, but after some inactivity play animation of going almost out of the screen
		on selecting next inventoryslot, update all the data from the item ptr in the inventoryslot*/

	//lets find the selected slot data
	 UInventorySlot* l_currInventorySlot = *mapRefInventorySlots.Find(currentlyActiveSlot);
	if (l_currInventorySlot == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	if (l_currInventorySlot->slotData.refItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot->slotData.refItem == nullptr"));
		return;
	}

	FItemData l_selectedItemData = l_currInventorySlot->slotData.refItem->GetCurrentItemData();

	
		
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

	//update refVerticalBoxItemEffects, here we add a child of another widget we create later TODO !!

}

void UInventoryWidget::UseSelectedItem()
{
	//lets find the selected slot data
	UInventorySlot* l_currInventorySlot = *mapRefInventorySlots.Find(currentlyActiveSlot);
	if (l_currInventorySlot == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	if (l_currInventorySlot->slotData.refItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot->slotData.refItem == nullptr"));
		return;
	}

	FItemData l_selectedItemData = l_currInventorySlot->slotData.refItem->GetCurrentItemData();

	if (l_selectedItemData.bIsOnCooldown == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("item on cd."));
		return;
	}

	//gets the functionality depending on item type
	switch (l_selectedItemData.itemType)
	{
	case EItemType::TOME:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype TOME"));
		
		//check what magic type the tome is
		switch (l_selectedItemData.itemAbility.magicType)
		{
		case ECardMagicTypes::NONE:
			break;
		case ECardMagicTypes::NATURE:
			break;
		case ECardMagicTypes::FIRE:
			//in this demo we do fire magic tome

			//for demo we just cast a spell and exhaust the item. Should the item get deleted or have cooldown?
			//i think probably best if item gets cooldown, but is expensive to use?

			break;
		case ECardMagicTypes::LIGHTNING:
			break;
		case ECardMagicTypes::ICE:
			break;
		case ECardMagicTypes::DARK:
			break;
		case ECardMagicTypes::CHAOS:
			break;
		case ECardMagicTypes::MIND:
			break;
		case ECardMagicTypes::EVIL:
			break;
		case ECardMagicTypes::HATRED:
			break;
		case ECardMagicTypes::BLOOD:
			break;
		case ECardMagicTypes::ANCIENT:
			break;
		case ECardMagicTypes::DIMENSIONAL:
			break;
		case ECardMagicTypes::ELDRITCH:
			break;
		case ECardMagicTypes::CELESTIAL:
			break;
		case ECardMagicTypes::CURSED:
			break;
		case ECardMagicTypes::DEMONIC:
			break;
		case ECardMagicTypes::TIME:
			break;
		case ECardMagicTypes::BEAST:
			break;
		case ECardMagicTypes::ILLUSION:
			break;
		case ECardMagicTypes::ENCHANTMENT:
			break;
		case ECardMagicTypes::ETHER:
			break;
		case ECardMagicTypes::SOUL:
			break;
		case ECardMagicTypes::VIOLET:
			break;
		case ECardMagicTypes::ISTHAN:
			break;
		case ECardMagicTypes::MYDIAN:
			break;
		default:
			break;
		}

		break;
	case EItemType::TOKEN:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype TOKEN"));
		break;
	case EItemType::SOUL:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype SOUL"));
		break;
	case EItemType::MYSTICAL:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype MYSTICAL"));
		break;
	}

	StartCooldownTimer(l_currInventorySlot->slotData.refItem);


	if (l_selectedItemData.bIsConsumedOnUse)
	{
		//remove item from inventory and destroy it TODO !!
	}
}

void UInventoryWidget::DropSelectedItem()
{

}



void UInventoryWidget::TimerRemoveCooldown(class AItem* iRefItem)
{
	UE_LOG(LogTemp, Warning, TEXT("cdtimer end"));
	iRefItem->currentItemData.bIsOnCooldown  = false;
}

void UInventoryWidget::StartCooldownTimer(class AItem* iRefItem)
{
	UE_LOG(LogTemp, Warning, TEXT("StartCDTImer"));
	FTimerHandle cdTimerHandle;
	FTimerDelegate cdTimerDelegate;
	cdTimerDelegate.BindUFunction(this, FName("TimerRemoveCooldown"), iRefItem);
	GetWorld()->GetTimerManager().SetTimer(cdTimerHandle, cdTimerDelegate, iRefItem->GetCurrentItemData().itemCooldown, false);
	iRefItem->currentItemData.bIsOnCooldown = true;
}


