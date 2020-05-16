// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventorySlot.h"
#include "TG/Libraries/InventoryLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "TG/Controllers/ExploreController.h"
#include "TG/TGCharacter.h"
#include "TG/Item/Item.h"
#include "TG/Components/InventoryComponent.h"
#include "PaperSprite.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	InitializeRefs();
	AddDelegateBindings();
	GetStartingSlot();



// 	FTimerHandle invWidgetInitializeWithTimer;
// 	GetWorld()->GetTimerManager().SetTimer(invWidgetInitializeWithTimer, this, &UInventoryWidget::InitializeWithTimer, 0.5f, false);


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
	
	HighlightSelectedSlot();
}

void UInventoryWidget::InitializeWithTimer()
{

}

void UInventoryWidget::AddDelegateBindings()
{
	refExplorePlayerController = Cast<AExploreController>(GetWorld()->GetFirstPlayerController());
	refExplorePlayerController->delegateInventoryMove.AddDynamic(this, &UInventoryWidget::MoveInInventory);
	//this is initialized with InitializeRefs, which at least atm is called before this so its safe
	refPlayerCharacter->GetInventoryComponent()->delegateInventoryUpdate.AddDynamic(this, &UInventoryWidget::UpdateItemsFromPlayerInventory);

	
}

void UInventoryWidget::InitializeRefs()
{
	//init player pawn ref
	refPlayerCharacter = Cast<ATGCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UInventoryWidget::MoveInInventory(EMoveDirections iMoveDir)
{
	FVector2D l_targetDirection = currentlyActiveSlot;
	switch (iMoveDir)
	{
	case EMoveDirections::UP:
		UE_LOG(LogTemp, Warning, TEXT("UP"));
		l_targetDirection.X -= 1;
		break;
	case EMoveDirections::DOWN:
		l_targetDirection.X += 1;
		UE_LOG(LogTemp, Warning, TEXT("DOWN"));
		break;
	case EMoveDirections::LEFT:
		l_targetDirection.Y -= 1;
		UE_LOG(LogTemp, Warning, TEXT("LEFT"));
		break;
	case EMoveDirections::RIGHT:
		l_targetDirection.Y += 1;
		UE_LOG(LogTemp, Warning, TEXT("RIGHT"));
		break;
	}
	if (mapRefInventorySlots.Find(l_targetDirection))
	{
		SelectNeighbourSlot(l_targetDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("direction where I wanted to move was invalid."));
	}
	
}

void UInventoryWidget::HighlightSelectedSlot()
{
	UInventorySlot* l_ref = *mapRefInventorySlots.Find(currentlyActiveSlot);
	l_ref->slotData.bIsSelected = true;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UInventoryWidget::DeHighlightLastSelectedSlot()
{
	UInventorySlot* l_ref = *mapRefInventorySlots.Find(lastActiveSlot);
	l_ref->slotData.bIsSelected = false;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UInventoryWidget::SelectNeighbourSlot(FVector2D iTarget)
{
	lastActiveSlot = currentlyActiveSlot;
	currentlyActiveSlot = iTarget;
	DeHighlightLastSelectedSlot();
	HighlightSelectedSlot();
}

void UInventoryWidget::GetStartingSlot()
{
	//makes the selection start somewhere from the middle, not really accurate and well thought out, good enough
	float l_column = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns;
	float l_rows = UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows;
		l_column = FMath::RoundHalfToEven(l_column / 2);
		l_rows = FMath::RoundHalfToEven(l_rows / 2);
	
		//this is just so that with 3x3 selection would be in the middle, there's probably a proper math formula for this
		l_column -= 1; 
		l_rows	 -= 1;

		//clamp it so it doesnt go over the column/row sizes, this function needs const parameters so making temp consts
		const int32 l_tmpClmn = l_column;
		const int32 l_tmpRows = l_rows;				
		l_column = FMath::Clamp(l_tmpClmn, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).columns);
		l_rows = FMath::Clamp(l_tmpRows, 0, UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType::BAG).rows);
	FVector2D midVec = FVector2D(l_column, l_rows);
	currentlyActiveSlot = midVec; //replace this
}

void UInventoryWidget::UpdateItemsFromPlayerInventory(TArray<class AItem*> iPlayerInventory)
{
	UE_LOG(LogTemp, Warning, TEXT(" UInventoryWidget::UpdateItemsFromPlayerInventory()"));
	TArray<UInventorySlot*> value;
	mapRefInventorySlots.GenerateValueArray(value);
	int32 ctr = 0;
	for (auto& e : iPlayerInventory)
	{
		FSlateBrush brush;
		brush.SetResourceObject(e->GetCurrentItemData().itemIcon);
		for (int i = ctr; i <= iPlayerInventory.Num() - 1; i++)
		{
			value[i]->refItemIcon->SetBrush(brush);
			value[i]->refItemIcon->SetBrushSize(FVector2D(45, 45));
		}
		ctr++;
	}
}

