// Fill out your copyright notice in the Description page of Project Settings.


#include "TGHUD.h"
#include "TG/UI/MainMenu/MainMenu.h"
#include "TG/UI/IngameMenu/IngameMenu.h"
#include "TG/UI/IngameInventoryMenu/IngameInventoryMenu.h"
#include "Components/Button.h"

void ATGHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();
	
	

}

void ATGHUD::InitializeWidgets()
{

	if (IngameMenuClass != nullptr)
	{
		refIngameMenu = CreateWidget<UIngameMenu>(GetWorld(), IngameMenuClass);
		if (refIngameMenu != nullptr)
		{
			refIngameMenu->AddToViewport();
			refIngameMenu->CloseIngameMenu();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("set the BP widget in TGHUD BP"));
	}

// 	if (IngameInventoryMenu!= nullptr)
// 	{
// 		refIngameInventoryMenu = CreateWidget<UIngameInventoryMenu>(GetWorld(), IngameInventoryMenu);
// 		if (refIngameInventoryMenu != nullptr)
// 		{
// 			refIngameInventoryMenu->AddToViewport();
// 		}
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("set the BP widget in TGHUD BP"));
// 	}

	//start adding bindings on widget buttons and stuff
	FTimerHandle timerHandleTGHUDMainMenuButtons;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandleTGHUDMainMenuButtons, this, &ATGHUD::InitializeIngameMenuComponents, 0.5f);

}

void ATGHUD::InitializeIngameMenuComponents()
{
	UButton* IngameMenuReturnButton = this->refIngameMenu->refReturnGameButton;
	IngameMenuReturnButton->OnClicked.AddDynamic(this, &ATGHUD::IngameMenu_ReturnButtonClicked);

	UButton* IngameMenuOptionsButton = this->refIngameMenu->refOptionsButton;
	IngameMenuOptionsButton->OnClicked.AddDynamic(this, &ATGHUD::IngameMenu_OptionsButtonClicked);

	UButton* IngameMenuQuitToMenuButton = this->refIngameMenu->refQuitGameButton;
	IngameMenuQuitToMenuButton->OnClicked.AddDynamic(this, &ATGHUD::IngameMenu_QuitButtonClicked);
}

void ATGHUD::ToggleIngameMenu()
{
	//simple toggle on/off
	if (refIngameMenu != nullptr)
	{
		refIngameMenu->GetVisibility() == ESlateVisibility::Visible ? 
			refIngameMenu->CloseIngameMenu() : refIngameMenu->OpenIngameMenu();	
		
	}
}

void ATGHUD::IngameMenu_ReturnButtonClicked()
{
	refIngameMenu->ReturnToGame();
}

void ATGHUD::IngameMenu_OptionsButtonClicked()
{
	refIngameMenu->Options();
}

void ATGHUD::IngameMenu_QuitButtonClicked()
{
	refIngameMenu->QuitGame();
}
