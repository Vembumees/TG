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
	FTimerHandle readDataTimer;
	GetWorld()->GetTimerManager().SetTimer(readDataTimer, this, &AMenuItem::ReadDataTable, 0.1);
}


void AMenuItem::ReadDataTable()
{
	
	UDataTable* itemInfo = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), 
		nullptr, TEXT("DataTable'/Game/TG/BP/Data/DT_MenuItemData.DT_MenuItemData'")));
	if (itemInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MenuItemData not found!"));
	}
	dataTableItemRowNames = itemInfo->GetRowNames();
	FItemMenuAllData* row = itemInfo->FindRow<FItemMenuAllData>(dataTableItemRowNames[dtItemDataRowNumber], TEXT("LookupMenuItemData"));
	if (row != nullptr)
	{
		currentMenuItemData = row->itemData;
	}
}

class AMenuItem* AMenuItem::SpawnItem(UWorld* iWorld, int32 iItemIdx)
{
	FActorSpawnParameters spawnParams;
	AMenuItem* spawnedItem = iWorld->SpawnActor<AMenuItem>(spawnParams);
	spawnedItem->dtItemDataRowNumber = iItemIdx;
	return spawnedItem;
}
