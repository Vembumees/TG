// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySlot.h"
#include "TG/Libraries/InventoryLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "TG/Controllers/ExploreController.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();

	AddDelegateBindings();

// 	FTimerHandle dsa;
// 	GetWorld()->GetTimerManager().SetTimer(dsa, this, &UInventoryWidget::CreateInventorySlots, 1.f, false);
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
}

void UInventoryWidget::AddDelegateBindings()
{
	AExploreController* pc = Cast<AExploreController>(GetWorld()->GetFirstPlayerController());
	pc->delegateInventoryMove.AddDynamic(this, &UInventoryWidget::MoveInInventory);
}

void UInventoryWidget::MoveInInventory(EMoveDirections iMoveDir)
{
	switch (iMoveDir)
	{
	case EMoveDirections::UP:

		UE_LOG(LogTemp, Warning, TEXT("UP"));
		break;
	case EMoveDirections::DOWN:

		UE_LOG(LogTemp, Warning, TEXT("DOWN"));
		break;
	case EMoveDirections::LEFT:

		UE_LOG(LogTemp, Warning, TEXT("LEFT"));
		break;
	case EMoveDirections::RIGHT:

		UE_LOG(LogTemp, Warning, TEXT("RIGHT"));
		break;
	}
}
