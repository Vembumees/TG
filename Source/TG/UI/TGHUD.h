// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TGHUD.generated.h"

/**
 * 
 */
UCLASS()
class TG_API ATGHUD : public AHUD
{
	GENERATED_BODY()

	
public: 

	void InitializeWidgets();
	void InitializeReferences();
	void InitializeIngameMenuComponents();
	

	/* ###########################################################
						Ingame Menu
	 ########################################################### */
	void IngameMenuToggle();

	void IngameMenuOpen();
	void IngameMenuClose();
	
	UFUNCTION()
	void IngameMenu_ReturnButtonClicked();
	UFUNCTION()
	void IngameMenu_OptionsButtonClicked();
	UFUNCTION()
	void IngameMenu_QuitButtonClicked();
	 /* #########################END############################## */
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UIngameMenu> IngameMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UIngameInventoryMenu> IngameInventoryMenu;


	/* ###########################################################
						widgets refs
	 ########################################################### */

	class UIngameMenu* refIngameMenu;
	class UIngameInventoryMenu* refIngameInventoryMenu;
	 /* #########################END############################## */

	/* ###########################################################
						refs
	 ########################################################### */
	 class AExploreController* refExplorePlayerController;
	 /* #########################END############################## */
};
