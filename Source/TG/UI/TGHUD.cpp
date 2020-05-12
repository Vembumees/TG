// Fill out your copyright notice in the Description page of Project Settings.


#include "TGHUD.h"
#include "TG/UI/IngameMenu/IngameMenu.h"
#include "TG/UI/IngameInventoryMenu/IngameInventoryMenu.h"
#include "TG/Controllers/ExploreController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ATGHUD::BeginPlay()
{
	Super::BeginPlay();
	InitializeReferences();
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
			IngameMenuClose();
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

	InitializeIngameMenuComponents();

}

void ATGHUD::InitializeReferences()
{
	 refExplorePlayerController = Cast<AExploreController>(GetWorld()->GetFirstPlayerController());
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

void ATGHUD::IngameMenuToggle()
{
	//simple toggle on/off
	if (refIngameMenu != nullptr)
	{	
		refIngameMenu->GetVisibility() == ESlateVisibility::Visible ? this->IngameMenuClose() : this->IngameMenuOpen();
	}
}

void ATGHUD::IngameMenuOpen()
{
	UWorld* World = GetWorld();
	//!! TODO also do a gamestate check
	UE_LOG(LogTemp, Log, TEXT("OpenIngameMenu()"));
	checkSlow(refIngameMenu->GetVisibility() == ESlateVisibility::Hidden); //only want to open from closed
	refIngameMenu->SetVisibility(ESlateVisibility::Visible);
		refExplorePlayerController->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		refExplorePlayerController->SetInputMode(InputMode);
		UGameplayStatics::SetGamePaused(this, true);
	
}

void ATGHUD::IngameMenuClose()
{
	UWorld* World = GetWorld();
	//!! TODO also do a gamestate check
	UE_LOG(LogTemp, Log, TEXT("CloseIngameMenu()"));
	checkSlow(refIngameMenu->GetVisibility() == ESlateVisibility::Visible); // only want to closed from open
	refIngameMenu->SetVisibility(ESlateVisibility::Hidden);



		refExplorePlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		refExplorePlayerController->SetInputMode(InputMode);
		UGameplayStatics::SetGamePaused(this, false);

}

void ATGHUD::IngameMenu_ReturnButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("ATGHUD::IngameMenu_ReturnButtonClicked()"));
	this->IngameMenuToggle();
}

void ATGHUD::IngameMenu_OptionsButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("ATGHUD::IngameMenu_OptionsButtonClicked()"));
}

void ATGHUD::IngameMenu_QuitButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("ATGHUD::IngameMenu_QuitButtonClicked()"));
	FName NextLevelName = TEXT("MapMainMenu");
	UGameplayStatics::OpenLevel(
		this->GetWorld(),
		NextLevelName);
}
