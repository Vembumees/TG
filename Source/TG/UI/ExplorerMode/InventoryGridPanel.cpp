// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridPanel.h"
#include "Components/InvalidationBox.h"
#include "Components/UniformGridPanel.h"
#include "InventorySlot.h"

void UInventoryGridPanel::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}


void UInventoryGridPanel::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	//here detect if mouse leaves the grid
}

