// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MainMenuSlot.h"
#include "TG/Controllers/MainMenuPlayerController.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"



void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeBPReferences();
	CreateMenuSlots();
	
}

void UMainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	InitializeBPReferences();
}

int32 UMainMenu::GetCurrentlySelectedSlotIndex()
{
// 	UMainMenuSlot* l_menuSlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
// 	return l_menuSlot->menuSlotData.slotIndex;
	return 0;
}


void UMainMenu::RefreshMenuSlots()
{
	UE_LOG(LogTemp, Error, TEXT("UMainMenu::RefreshMenuSlots()"));
	CreateMenuSlots();
}

void UMainMenu::AddDelegateBindings()
{
	refMainMenuPlayerController = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
	refMainMenuPlayerController->delegateMenuMove.AddDynamic(this, &UMainMenu::MoveInMenu);
	refMainMenuPlayerController->delegateMenuUse.AddDynamic(this, &UMainMenu::UseSelectedSlot);
}

void UMainMenu::InitializeRefs()
{

}

void UMainMenu::CreateMenuSlots()
{
	/*if i miracelously get this to working then add stuff to the uinventorylibrary, sizes and all kinds of stats for the different
	menu types*/
	if (refMenuUniformGridPanel == nullptr)
	{
		return;
	}
	TArray<UMainMenuSlot*> slotOld = mainMenuSlotsInventory;
	int32 l_column = 10;
	int32 l_rows = 1;
	int32 l_nrOfSlots = (l_rows * l_column) - 1;
	mapRefMenuSlots.Empty();
	mainMenuSlotsInventory.Empty();
	refMenuUniformGridPanel->ClearChildren();
	menuInvSize = 100;
	for (int i = 0; i <= l_nrOfSlots; i++)
	{
		/*dnt forget to update the class in wbp*/
		UMainMenuSlot* wMenuInvSlot = CreateWidget<UMainMenuSlot>(GetWorld(), menuSlotClass);
		int32 l_currColumn = i / l_column;
		int32 l_currRow = i - ((i / l_column) * l_column);
		refMenuUniformGridPanel->AddChildToUniformGrid(wMenuInvSlot, l_currColumn, l_currRow);
		mapRefMenuSlots.Add(FVector2D(l_currColumn, l_currRow), wMenuInvSlot);
		wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::EMPTY;
		if (slotOld.IsValidIndex(1))	//TODO !! idk i have no idea how this doesnt or yet hasnt caused a bug
		{
			if (slotOld[i]->menuSlotData.menuInventorySlotState == EInventorySlotState::EMPTY)
			{
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::EMPTY;
				wMenuInvSlot->menuSlotData.refMenuItem = nullptr;
			}
			else
			{
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::HASITEM;
				wMenuInvSlot->menuSlotData.refMenuItem = slotOld[i]->menuSlotData.refMenuItem;
			}
		}

		wMenuInvSlot->menuSlotData.slotIndex = i;
		wMenuInvSlot->menuSlotData.menuType = EMenuType::MAINMENU;
		wMenuInvSlot->refWSizeBoxSlotSize->SetHeightOverride(menuInvSize);
		wMenuInvSlot->refWSizeBoxSlotSize->SetWidthOverride(menuInvSize);

		mainMenuSlotsInventory.Add(wMenuInvSlot);

	}
	

	HighlightSelectedSlot();
}

void UMainMenu::UseSelectedSlot()
{

}

void UMainMenu::HighlightSelectedSlot()
{
	UMainMenuSlot* l_ref = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	l_ref->menuSlotData.bIsSelected = true;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UMainMenu::DeHighlightSelectedSlot()
{
	UMainMenuSlot* l_ref = *mapRefMenuSlots.Find(lastSelectedSlotCoord);
	l_ref->menuSlotData.bIsSelected = false;
	l_ref->UpdateInventoryButtonBackgroundType();
}

void UMainMenu::SelectNeightbourSlot(FVector2D iTarget)
{
	lastSelectedSlotCoord = currentlySelectedSlotCoord;
}

void UMainMenu::GetStartingSlot()
{
	currentlySelectedSlotCoord = FVector2D(0, 0);
}

void UMainMenu::MoveInMenu(EMoveDirections iMoveDir)
{
	FVector2D l_targetDirection = currentlySelectedSlotCoord;
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
	if (mapRefMenuSlots.Find(l_targetDirection))
	{
		SelectNeightbourSlot(l_targetDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("direction where I wanted to move was invalid."));
	}
}

