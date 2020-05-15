// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class AItem*> refItemInventory;

public:	

	bool AddItemToInventory(class AItem* iItem);

	void DeleteItemFromIndex(int32 iIndex);
	
	UPROPERTY(VisibleAnywhere)
	int32 inventoryMaxSize;


};
