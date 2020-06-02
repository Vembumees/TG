// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class TG_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void InitializeWidgets();
	void InitializeIngameMenuComponents();
	void InitializePlayerInput();

	UFUNCTION()
		void MainMenu_PlayButtonClicked();
	UFUNCTION()
		void MainMenu_OptionsButtonClicked();
	UFUNCTION()
		void MainMenu_AboutButtonClicked();
	UFUNCTION()
		void MainMenu_ExitButtonClicked();
protected:
	virtual void BeginPlay() override;

	class AMainMenuPlayerController* refMainMenuController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMainMenu> MainMenuClass;

	class UMainMenu* refMainMenu;

	FName mapDemo = TEXT("MapDemoLevel");
	FName mapLevel1 = TEXT("map_Level1");
	FName mapLevel2 = TEXT("map_Level2");

	void SetIsFocusable(bool ibIsFocusable);
};
