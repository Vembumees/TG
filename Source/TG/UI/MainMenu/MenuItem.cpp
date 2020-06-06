// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuItem.h"
#include "PaperFlipbook.h"
#include "Engine/DataTable.h"

// Sets default values
AMenuItem::AMenuItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMenuItem::BeginPlay()
{
	Super::BeginPlay();
	ReadDataTable();
}


void AMenuItem::ReadDataTable()
{
	
	UDataTable* itemInfo = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), 
		nullptr, TEXT("DataTable'/Game/TG/BP/Data/DT_MenuItemData.DT_MenuItemData'")));
	if (itemInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MenuItemData not found!"));
	}
	FItemMenuAllData* row = itemInfo->FindRow<FItemMenuAllData>(dataTableItemRowNames[dtItemDataRowNumber], TEXT("LookupMenuItemData"));
	if (row != nullptr)
	{
		currentMenuItemData = row->itemData;
	}
}
