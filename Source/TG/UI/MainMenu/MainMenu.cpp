// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MainMenuSlot.h"
#include "TG/Controllers/MainMenuPlayerController.h"




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

