// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TG/Enumerations.h"
#include "MainMenuPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuMove, EMoveDirections, currMenuMoveDirection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuUseSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDebugAdditem);


UCLASS()
class TG_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainMenuPlayerController();

protected:
	virtual void SetupInputComponent() override;

	void MenuUP();
	void MenuDOWN();
	void MenuLEFT();
	void MenuRIGHT();
	void MenuUSESELECTED();
	void InitializeRefs();
	void DebugAdditem();




public:

	EMoveDirections     currMenuMoveDirection;
	FMenuMove	   		delegateMenuMove;
	FMenuUseSelected    delegateMenuUse;
	FDebugAdditem		delegateDebugAddItem;

	/* ###########################################################
					references
	 ########################################################### */
public:
	UPROPERTY()
		class AMainMenuHUD* refMainMenuHUD;

	/* #########################END############################## */
};
