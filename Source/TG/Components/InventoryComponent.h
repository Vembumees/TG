// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUpdate, TArray<class UInventorySlot*>, refItemInventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UInventorySlot*> refItemInventory;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;




	void InitializeReferences();
	void InitializeInventory();

public:	

	bool AddItemToInventory(class AItem* iItem);

	void DeleteItemFromInventory(int32 iIdx);

	void SwapItemInInventory(int32 iStartIdx, int32 iDestinationIdx);

	void MoveItemToAnotherSlot(int32 iStartIdx, int32 iDestinationIdx);

	bool CheckIfSlotHasItem(int32 iIdx);

	void AddItemToArtifactSlot(int32 iIdx);

	void CreateStartingItems();

	TArray<class UInventorySlot*> GetItemInventory();

	UPROPERTY(VisibleAnywhere)
	int32 inventoryMaxSize;

	class UInventoryWidget* refInventoryWidget;

	FInventoryUpdate delegateInventoryUpdate;

private:
	void RefreshInventorySlots();
};
