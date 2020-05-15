// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

	inventoryMaxSize = 8; //this is cuz atm inventorysize is 9x9, later get the invsize !! TODO
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UInventoryComponent::AddItemToInventory(class AItem* iItem)
{
	if (iItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryComponent::AddItemToInventory fail, item nullptr"));
		return false;
	}

	if (refItemInventory.IsValidIndex(inventoryMaxSize))
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory is full"));
		return false;
	}
	 
	refItemInventory.Add(iItem);
	UE_LOG(LogTemp, Error, TEXT("Added item successfully."));
	return true;
}

void UInventoryComponent::DeleteItemFromIndex(int32 iIndex)
{

}

