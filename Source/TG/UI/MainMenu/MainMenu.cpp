// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MainMenuSlot.h"
#include "TG/Controllers/MainMenuPlayerController.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TG/Libraries/InventoryLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TG/StaticLibrary.h"
#include "TG/UI/MainMenu/MenuItem.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSprite.h"
#include "Components/Image.h"

#define MAINMENU_ICONSIZE FVector2D(90, 90)

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeBPReferences();
	CreateMenuSlots();
	AddDelegateBindings();
	GetStartingSlot();
	CreateMenuStartingItems();
	UpdateTooltipText();
	
}

void UMainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();	 
}

void UMainMenu::CreateMenuStartingItems()
{
	TArray<AMenuItem*> l_items;
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 0));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 1));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 2));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 3));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 3));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 3));
	l_items.Add(AMenuItem::SpawnItem(this->GetWorld(), 3));
	for (auto& e : l_items)
	{
		AddItemToInventory(e);
	}

}

bool UMainMenu::AddItemToInventory(class AMenuItem* iItem)
{
	if (iItem == nullptr)
	{
		return false;
	}

	if (this->GetFirstEmptyInventorySlotIndex() == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("MenuInventory is full"));
		return false;
	}
	int32 idx = this->GetFirstEmptyInventorySlotIndex();
	mainMenuSlotsInventory[idx]->menuSlotData.refMenuItem = iItem;
	mainMenuSlotsInventory[idx]->menuSlotData.menuInventorySlotState = EInventorySlotState::HASITEM;
	UE_LOG(LogTemp, Error, TEXT("Added menu item successfully."));
	//if i dont do this with timer and above 0.1 seconds timer icons are for some reason white
	FTimerHandle addItemRefreshSlots;
	GetWorld()->GetTimerManager().SetTimer(addItemRefreshSlots, this, &UMainMenu::RefreshMenuSlots, 0.15);
	return true;
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
	UpdateItemsFromMenuInventory(mainMenuSlotsInventory);
}

void UMainMenu::UpdateItemsFromMenuInventory(TArray<class UMainMenuSlot*> iMenuInventory)
{
	TArray<UMainMenuSlot*> mapValues;
	mapRefMenuSlots.GenerateValueArray(mapValues);
	int32 loopCounter = 0;
	for (auto& e : iMenuInventory)
	{
		if (e->menuSlotData.menuInventorySlotState == EInventorySlotState::HASITEM)
		{
			FSlateBrush brush;
			brush.SetResourceObject(e->menuSlotData.refMenuItem->currentMenuItemData.itemIcon);
			//update icon
			mapValues[loopCounter]->refSlotItemIcon->SetBrush(brush);
			mapValues[loopCounter]->refSlotItemIcon->SetBrushSize(MAINMENU_ICONSIZE);

			//add item pointer
			mapValues[loopCounter]->menuSlotData.refMenuItem = e->menuSlotData.refMenuItem;
		}
		loopCounter++;
	}
}


void UMainMenu::DebugAction1()
{
	//using this just to debug whatever crap i need currently
	
	/*AddItemToInventory(AMenuItem::SpawnItem(this->GetWorld(), 0));*/

	GetCurrentSelectedRowIndexes(currentlySelectedSlotCoord);
}

void UMainMenu::DebugAction2()
{
	GetCurrentSelectedColumnIndexes(currentlySelectedSlotCoord);
}

void UMainMenu::AddDelegateBindings()
{
	refMainMenuPlayerController = Cast<AMainMenuPlayerController>(GetWorld()->GetFirstPlayerController());
	refMainMenuPlayerController->delegateMenuMove.AddDynamic(this, &UMainMenu::MoveInMenu);
	refMainMenuPlayerController->delegateMenuUsePRESSED.AddDynamic(this, &UMainMenu::UseSelectedSlotPressed);
	refMainMenuPlayerController->delegateMenuUseRELEASED.AddDynamic(this, &UMainMenu::UseSelectedSlot);
	refMainMenuPlayerController->delegateDebugAction1.AddDynamic(this, &UMainMenu::DebugAction1);
	refMainMenuPlayerController->delegateDebugAction2.AddDynamic(this, &UMainMenu::DebugAction2);
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
	int32 l_column = UInventoryLibrary::GetMenuInventoryGridData(EMenuType::MAINMENU).columns;
	int32 l_rows = UInventoryLibrary::GetMenuInventoryGridData(EMenuType::MAINMENU).rows;
	TArray<int32> l_hiddenSlotIndexes = UInventoryLibrary::GetMenuInventoryGridData(EMenuType::MAINMENU).hiddenIndexes;
	int32 l_nrOfSlots = (l_rows * l_column) - 1;
	mapRefMenuSlots.Empty();
	mainMenuSlotsInventory.Empty();
	refMenuUniformGridPanel->ClearChildren();
	menuInvSize = UInventoryLibrary::GetMenuInventorySlotSize(EMenuType::MAINMENU);
	for (int i = 0; i <= l_nrOfSlots; i++)
	{
		/*dnt forget to update the class in wbp*/
		UMainMenuSlot* wMenuInvSlot = CreateWidget<UMainMenuSlot>(GetWorld(), menuSlotClass);
		int32 l_currColumn = i / l_column;
		int32 l_currRow = i - ((i / l_column) * l_column);
		refMenuUniformGridPanel->AddChildToUniformGrid(wMenuInvSlot, l_currColumn, l_currRow);
		mapRefMenuSlots.Add(FVector2D(l_currColumn, l_currRow), wMenuInvSlot);
		wMenuInvSlot->menuSlotData.slotCoords = FVector2D(l_currColumn, l_currRow);
		wMenuInvSlot->menuSlotData.slotIndex = i;
		wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::EMPTY;
		wMenuInvSlot->menuSlotData.menuType = EMenuType::MAINMENU;
		wMenuInvSlot->refWSizeBoxSlotSize->SetHeightOverride(menuInvSize);
		wMenuInvSlot->refWSizeBoxSlotSize->SetWidthOverride(menuInvSize);

		if (slotOld.IsValidIndex(0)) //just checks if the thing is empty or not
		{
			switch (slotOld[i]->menuSlotData.menuInventorySlotState)
			{
			case EInventorySlotState::EMPTY:
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::EMPTY;
				wMenuInvSlot->menuSlotData.refMenuItem = nullptr;
				break;
			case EInventorySlotState::HASITEM:
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::HASITEM;
				wMenuInvSlot->menuSlotData.refMenuItem = slotOld[i]->menuSlotData.refMenuItem;
				break;
			case EInventorySlotState::HIDDEN:
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::HIDDEN;
				break;
			case EInventorySlotState::DISABLED:
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::DISABLED;
				break;
			}
		}

		for (auto& e : l_hiddenSlotIndexes)
		{
			if (i == e)
			{
				wMenuInvSlot->menuSlotData.menuInventorySlotState = EInventorySlotState::HIDDEN;
				//set opacity of the slot to 0
				wMenuInvSlot->SetRenderOpacity(0);
			}
		}

		

		mainMenuSlotsInventory.Add(wMenuInvSlot);

	}
	

	HighlightSelectedSlot();
}



void UMainMenu::UseSelectedSlotPressed()
{
	if (!mapRefMenuSlots.Contains(currentlySelectedSlotCoord))
	{
		return;
	}
	UMainMenuSlot* l_currMenuSlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	if (l_currMenuSlot->menuSlotData.refMenuItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("no item in slot"));
		return;
	}
	//sets the icon to pressed
	FSlateBrush brush;
	brush.SetResourceObject(l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.itemIconPressed);
	//update icon
	l_currMenuSlot->refSlotItemIcon->SetBrush(brush);
	l_currMenuSlot->refSlotItemIcon->SetBrushSize(MAINMENU_ICONSIZE);

	//Play sfx
	UGameplayStatics::PlaySound2D(GetWorld(), l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.sfxUseItem);
}

void UMainMenu::UseSelectedSlot()
{
	if (!mapRefMenuSlots.Contains(currentlySelectedSlotCoord))
	{
		return;
	}
	UMainMenuSlot* l_currMenuSlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	if (l_currMenuSlot->menuSlotData.refMenuItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("no item in slot"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("\n SLOTDATA \n slotIndex: %i \n itemName: %s \n menuType: %s \n menuInventorySlotState: %s"),
		l_currMenuSlot->menuSlotData.slotIndex,
		*l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.itemName,
		*UStaticLibrary::GetEnumValueAsString("EMenuType", l_currMenuSlot->menuSlotData.menuType ),
		*UStaticLibrary::GetEnumValueAsString("EInventorySlotState", l_currMenuSlot->menuSlotData.menuInventorySlotState)
	);

	//sets the icon to normal from pressed
	FSlateBrush brush;
	brush.SetResourceObject(l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.itemIcon);
	//update icon
	l_currMenuSlot->refSlotItemIcon->SetBrush(brush);
	l_currMenuSlot->refSlotItemIcon->SetBrushSize(MAINMENU_ICONSIZE);

	switch (l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.itemType)
	{
	case EMenuItemFunction::NONE:
		break;
	case EMenuItemFunction::STARTGAME:
		//open quest select

		UGameplayStatics::OpenLevel(
			this->GetWorld(),
			TEXT("MapDemoLevel"));

		break;
	case EMenuItemFunction::OPENSETTINGS:
		//open settings bars
		break;
	case EMenuItemFunction::QUITGAME:

		UKismetSystemLibrary::QuitGame(GetWorld(), this->GetOwningPlayer(), EQuitPreference::Quit, false);

		break;
	case EMenuItemFunction::D:
		break;
	case EMenuItemFunction::E:
		break;
	case EMenuItemFunction::F:
		break;
	case EMenuItemFunction::G:
		break;
	case EMenuItemFunction::H:
		break;
	case EMenuItemFunction::I:
		break;
	case EMenuItemFunction::J:
		break;
	case EMenuItemFunction::K:
		break;
	case EMenuItemFunction::L:
		break;
	case EMenuItemFunction::M:
		break;
	default:
		break;

	}




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
	//sets the icon back to normal from pressed
	UMainMenuSlot* l_currMenuSlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	//sets the icon to pressed
	FSlateBrush brush;
	brush.SetResourceObject(l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.itemIcon);
	//update icon
	l_currMenuSlot->refSlotItemIcon->SetBrush(brush);
	l_currMenuSlot->refSlotItemIcon->SetBrushSize(MAINMENU_ICONSIZE);

	lastSelectedSlotCoord = currentlySelectedSlotCoord;
	currentlySelectedSlotCoord = iTarget;
	DeHighlightSelectedSlot();
	HighlightSelectedSlot();
	UpdateTooltipText();

	//Play sfx
	UGameplayStatics::PlaySound2D(GetWorld(), l_currMenuSlot->menuSlotData.refMenuItem->currentMenuItemData.sfxHoverItem);

}

void UMainMenu::GetStartingSlot()
{
	for (auto& e : mainMenuSlotsInventory)
	{
		if (e->menuSlotData.menuInventorySlotState != EInventorySlotState::HIDDEN &&
			e->menuSlotData.menuInventorySlotState != EInventorySlotState::DISABLED)
		{
			
			currentlySelectedSlotCoord = e->menuSlotData.slotCoords;
			HighlightSelectedSlot();
			break;
		}
	}

}



void UMainMenu::GetCurrentSelectedRowIndexes(FVector2D iCurrentlySelectedSlot)
{
	//lets find the selected slot data
	UMainMenuSlot* l_currMenuInventorySlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	if (l_currMenuInventorySlot == nullptr)
	{
		refMenuTooltipText->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	//so, for finding row, we just need to +1 or -1 X. For COlumn 
	FVector2D l_currCoord = currentlySelectedSlotCoord;
	//add +1 to X.
	//if the coordinate is valid, add the valid slots index to array
	//if coordinate isn't valid, break loop and do the same loop for -1 to x.

	int yCoord = l_currCoord.Y;
	for (int xCoord = l_currCoord.X; mapRefMenuSlots.Find(FVector2D(xCoord, yCoord)) != nullptr; xCoord++)
	{
		auto& l_slots = *mapRefMenuSlots.Find(FVector2D(xCoord, yCoord));
		UE_LOG(LogTemp, Warning, TEXT("GetCurrentlySelectedRowIndexes();  FVector(%s), index %i"),
			*l_slots->menuSlotData.slotCoords.ToString(),
			l_slots->menuSlotData.slotIndex);

	}
}

void UMainMenu::GetCurrentSelectedColumnIndexes(FVector2D iCurrentlySelectedSlot)
{
	//lets find the selected slot data
	UMainMenuSlot* l_currMenuInventorySlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	if (l_currMenuInventorySlot == nullptr)
	{
		refMenuTooltipText->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	//so, for finding row, we just need to +1 or -1 X. For COlumn 
	FVector2D l_currCoord = currentlySelectedSlotCoord;
	//add +1 to X.
	//if the coordinate is valid, add the valid slots index to array
	//if coordinate isn't valid, break loop and do the same loop for -1 to x.

	int xCoord = l_currCoord.X;
	for (int yCoord = l_currCoord.Y; mapRefMenuSlots.Find(FVector2D(xCoord, yCoord)) != nullptr; yCoord++)
	{
		auto& l_slots = *mapRefMenuSlots.Find(FVector2D(xCoord, yCoord));
		UE_LOG(LogTemp, Warning, TEXT("GetCurrentlySelectedColumnIndexes();  FVector(%s), index %i"),
			*l_slots->menuSlotData.slotCoords.ToString(),
			l_slots->menuSlotData.slotIndex);

	}
}

void UMainMenu::UpdateTooltipText()
{
	//lets find the selected slot data
	UMainMenuSlot* l_currMenuInventorySlot = *mapRefMenuSlots.Find(currentlySelectedSlotCoord);
	if (l_currMenuInventorySlot == nullptr)
	{
		refMenuTooltipText->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot == nullptr"));
		return;
	}

	if (l_currMenuInventorySlot->menuSlotData.menuInventorySlotState == EInventorySlotState::EMPTY)
	{
		refMenuTooltipText->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget: l_currInventorySlot->slotData.refItem == nullptr"));
		return;
	}

	FMenuItemData l_selectedMenuItemData = l_currMenuInventorySlot->menuSlotData.refMenuItem->currentMenuItemData;
	
	//update item name
	refMenuTooltipText->SetText(FText::FromString(l_selectedMenuItemData.itemName));
	refMenuTooltipText->SetVisibility(ESlateVisibility::Visible);
}

int32 UMainMenu::GetFirstEmptyInventorySlotIndex()
{
	TArray<UMainMenuSlot*> mapValues;
	mapRefMenuSlots.GenerateValueArray(mapValues);
	for (auto& e : mapValues)
	{
		//will add item if slot is empty
		if (e->menuSlotData.menuInventorySlotState == EInventorySlotState::EMPTY)
		{
			return e->menuSlotData.slotIndex;
		}
	}

	//inv full
	return -1;

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
	//if slot is not valid or is hidden then dont move
	if (mapRefMenuSlots.Find(l_targetDirection))
	{
		UMainMenuSlot* l_slot = *mapRefMenuSlots.Find(l_targetDirection);
		if (l_slot->menuSlotData.menuInventorySlotState != EInventorySlotState::HIDDEN &&
			l_slot->menuSlotData.menuInventorySlotState != EInventorySlotState::DISABLED)
		{
			SelectNeightbourSlot(l_targetDirection);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("direction where I wanted to move is hidden."));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("direction where I wanted to move is invalid."));
	}
	
}

