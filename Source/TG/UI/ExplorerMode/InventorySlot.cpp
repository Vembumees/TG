// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}

void UInventorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	InitializeRefsInBP();
}
