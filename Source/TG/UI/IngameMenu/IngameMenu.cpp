// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameMenu.h"
#include "TG/Controllers/ExploreController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UIngameMenu::ReturnToGame()
{
	UE_LOG(LogTemp, Log, TEXT("UIngameMenu::ReturnToGame()"));
	this->CloseIngameMenu();
}

void UIngameMenu::Options()
{
	UE_LOG(LogTemp, Log, TEXT("UIngameMenu::Options()"));
}

void UIngameMenu::QuitGame()
{
	UE_LOG(LogTemp, Log, TEXT("UIngameMenu::QuitGame()"));
	if (refExploreController)
	{
		UWorld* world = GetWorld();
		if (world != nullptr)
		{
			//TODO !! later should just redirect to main menu
			UKismetSystemLibrary::QuitGame(world, world->GetFirstPlayerController(), EQuitPreference::Quit, false);
		}
	}
}

void UIngameMenu::OpenIngameMenu()
{
	//!! TODO also do a gamestate check
	UE_LOG(LogTemp, Log, TEXT("UIngameMenu::OpenIngameMenu()"));
	checkSlow(this->GetVisibility() == ESlateVisibility::Hidden); //only want to open from closed
	this->SetVisibility(ESlateVisibility::Visible);

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AExploreController* exploreController = Cast<AExploreController>(World->GetFirstPlayerController());
		if (exploreController)
		{
			exploreController->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			exploreController->SetInputMode(InputMode);
			UGameplayStatics::SetGamePaused(this, true);
		}
	}
}

void UIngameMenu::CloseIngameMenu()
{
	//!! TODO also do a gamestate check
	UE_LOG(LogTemp, Log, TEXT("UIngameMenu::CloseIngameMenu()"));
	checkSlow(this->GetVisibility() == ESlateVisibility::Visible); // only want to closed from open
	this->SetVisibility(ESlateVisibility::Hidden);

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* exploreController = World->GetFirstPlayerController();
		if (exploreController)
		{
			exploreController->bShowMouseCursor = false;
			FInputModeGameOnly InputMode;
			exploreController->SetInputMode(InputMode);
			UGameplayStatics::SetGamePaused(this, false);
		}
	}
}

void UIngameMenu::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeBPReferences();
}
