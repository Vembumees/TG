// Fill out your copyright notice in the Description page of Project Settings.


#include "TGHUD.h"
#include "TG/UI/MainMenu/MainMenu.h"
#include "TG/UI/IngameMenu/IngameMenu.h"
#include "TG/UI/IngameInventoryMenu/IngameInventoryMenu.h"

void ATGHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();

}

void ATGHUD::InitializeWidgets()
{
	if (MainMenuClass != nullptr)
	{
		refMainMenu = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		if (refMainMenu != nullptr)
		{
			refMainMenu->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("set the BP widget in TGHUD BP"));
	}

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
