// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "TG/UI/MainMenu/MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TG/Controllers/MainMenuPlayerController.h"


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgets();
	InitializePlayerInput();
	InitializeIngameMenuComponents();
}

void AMainMenuHUD::InitializeWidgets()
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
}

void AMainMenuHUD::InitializeIngameMenuComponents()
{
	UButton* MainMenuPlayButton = this->refMainMenu->refPlayGameButton;
	MainMenuPlayButton->OnClicked.AddDynamic(this, &AMainMenuHUD::MainMenu_PlayButtonClicked);

	UButton* MainMenuOptionsButton = this->refMainMenu->refOptionsButton;
	MainMenuOptionsButton->OnClicked.AddDynamic(this, &AMainMenuHUD::MainMenu_OptionsButtonClicked);

	UButton* MainMenuAboutButton = this->refMainMenu->refAboutButton;
	MainMenuAboutButton->OnClicked.AddDynamic(this, &AMainMenuHUD::MainMenu_AboutButtonClicked);

	UButton* MainMenuExitButton = this->refMainMenu->refExitGameButton;
	MainMenuExitButton->OnClicked.AddDynamic(this, &AMainMenuHUD::MainMenu_ExitButtonClicked);
}

void AMainMenuHUD::InitializePlayerInput()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		refMainMenuController = Cast<AMainMenuPlayerController>(World->GetFirstPlayerController());
		if (refMainMenuController)
		{
			refMainMenuController->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			refMainMenuController->SetInputMode(InputMode);
			UGameplayStatics::SetGamePaused(this, true);
		}
	}
}

void AMainMenuHUD::MainMenu_PlayButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("AMainMenuHUD::MainMenu_PlayButtonClicked()"));
	this->refMainMenu->RemoveFromParent();

	
	UGameplayStatics::OpenLevel(
		this->GetWorld(),
		mapDemo);

	//todo !! make level select widget
}	

void AMainMenuHUD::MainMenu_OptionsButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("AMainMenuHUD::MainMenu_OptionsButtonClicked())"));
}

void AMainMenuHUD::MainMenu_AboutButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("AMainMenuHUD::MainMenu_AboutButtonClicked()"));
}

void AMainMenuHUD::MainMenu_ExitButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("AMainMenuHUD::MainMenu_ExitButtonClicked()"));
	UKismetSystemLibrary::QuitGame(GetWorld(), this->PlayerOwner, EQuitPreference::Quit, false);
}