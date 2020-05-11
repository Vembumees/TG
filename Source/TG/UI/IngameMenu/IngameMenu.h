// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameMenu.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UIngameMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	/* ###########################################################
						GameMenu
	 ########################################################### */
	
	void ReturnGame();
	void Options();
	void QuitGame();

	void OpenIngameMenu();
	void CloseIngameMenu();
	
	
	 /* #########################END############################## */

	/* ###########################################################
						References
	 ########################################################### */
	 /*passes the UMG variables from BP to here*/
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeBPReferences();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refReturnGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refOptionsButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* refQuitGameButton;


		class AExploreController* refExploreController;
	 
	 /* #########################END############################## */


protected:
	virtual void NativeConstruct() override;

};
