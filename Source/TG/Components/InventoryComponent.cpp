// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

	inventoryCompWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("inventoryWidgetComp"));
	inventoryCompWidget->SetRelativeLocation(FVector(0, 0, 250));
	inventoryCompWidget->SetVisibility(true);
	inventoryCompWidget->SetCollisionProfileName(TEXT("NoCollision"));
	inventoryCompWidget->SetGenerateOverlapEvents(false);
	inventoryCompWidget->SetWidgetSpace(EWidgetSpace::Screen);
}


class UWidgetComponent* UInventoryComponent::GetInventoryCompWidget()
{
	return inventoryCompWidget;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

