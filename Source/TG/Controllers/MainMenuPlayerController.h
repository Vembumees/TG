// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TG/Enumerations.h"
#include "MainMenuPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuMove, EMoveDirections, currMenuMoveDirection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuUseSelected);


UCLASS()
class TG_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainMenuPlayerController();

protected:

	void MenuUP();
	void MenuDOWN();
	void MenuLEFT();
	void MenuRIGHT();
	void MenuUSESELECTED();
	void InitializeRefs();


	virtual void SetupInputComponent() override;

public:

	EMoveDirections     currMenuMoveDirection;
	FMenuMove	   		delegateMenuMove;
	FMenuUseSelected    delegateMenuUse;

	/* ###########################################################
					references
	 ########################################################### */
public:
	UPROPERTY()
		class AMainMenuHUD* refMainMenuHUD;

	/* #########################END############################## */
};
