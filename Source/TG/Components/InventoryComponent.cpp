// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TG/Controllers/ExploreController.h"
#include "TG/UI/TGHUD.h"
#include "TG/UI/ExplorerMode/InventorySlot.h"
#include "TG/UI/ExplorerMode/InventoryWidget.h"
#include "TG/UI/ExplorerMode/ExplorerModeScreen.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

	inventoryMaxSize = 8; //this is cuz atm inventorysize is 9x9, later get the invsize !! TODO
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeReferences();

}

void UInventoryComponent::InitializeReferences()
{
	//get inventorywidget ref
	ATGHUD* hud = Cast<ATGHUD>(Cast<AExploreController>(GetWorld()->GetFirstPlayerController())->GetHUD());
	refInventoryWidget = hud->GetRefExplorerModeScreen()->refInventoryWidget;


}

bool UInventoryComponent::AddItemToInventory(class AItem* iItem)
{
	if (iItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryComponent::AddItemToInventory fail, item nullptr"));
		return false;
	}

	if( refInventoryWidget->GetFirstEmptyInventorySlotIndex() == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory is full"));
		return false;
	}	
	int32 idx = refInventoryWidget->GetFirstEmptyInventorySlotIndex();
	refItemInventory[idx]->slotData.refItem = iItem;
	refItemInventory[idx]->slotData.inventorySlotState = EInventorySlotState::HASITEM;

	UE_LOG(LogTemp, Error, TEXT("Added item successfully."));
	//also update player UI via delegate
	delegateInventoryUpdate.Broadcast(refItemInventory);



	return true;
}

void UInventoryComponent::DeleteItemFromInventory(int32 iIdx)
{
	//delete item
	if (!refItemInventory.IsValidIndex(iIdx))
	{
		UE_LOG(LogTemp, Error, TEXT("deleteItemFromInventory - invalid index"));
		return;
	}


	refItemInventory[iIdx]->slotData.refItem = nullptr;
	refItemInventory[iIdx]->slotData.inventorySlotState = EInventorySlotState::EMPTY;
	delegateInventoryUpdate.Broadcast(refItemInventory);
}

void UInventoryComponent::SwapItemInInventory(int32 iStartIdx, int32 iDestinationIdx)
{
	//Swap refs and update ui
	AItem* tempItem = refItemInventory[iStartIdx]->slotData.refItem;
	refItemInventory[iStartIdx]->slotData.refItem =	refItemInventory[iDestinationIdx]->slotData.refItem;
	refItemInventory[iDestinationIdx]->slotData.refItem = tempItem;
	delegateInventoryUpdate.Broadcast(refItemInventory);
}

void UInventoryComponent::MoveItemToAnotherSlot(int32 iStartIdx, int32 iDestinationIdx)
{
	//move item to destination slot and delete ref from old slot
	refItemInventory[iDestinationIdx]->slotData.refItem = refItemInventory[iStartIdx]->slotData.refItem;
	refItemInventory[iDestinationIdx]->slotData.inventorySlotState = EInventorySlotState::HASITEM;

	refItemInventory[iStartIdx]->slotData.refItem = nullptr;
	refItemInventory[iStartIdx]->slotData.inventorySlotState = EInventorySlotState::EMPTY;


	delegateInventoryUpdate.Broadcast(refItemInventory);
}

bool UInventoryComponent::CheckIfSlotItemIsStillValid(int32 iIdx)
{
	if (refItemInventory[iIdx]->slotData.refItem == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}

}

TArray<class UInventorySlot*> UInventoryComponent::GetItemInventory()
{
	return refItemInventory;
}


