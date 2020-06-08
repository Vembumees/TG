// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TG/Enumerations.h"
#include "MainMenuPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuMove, EMoveDirections, currMenuMoveDirection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuUseSelectedPRESSED);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuUseSelectedRELEASED);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDebugAction1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDebugAction2);


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
	void MenuUSESELECTEDPRESSED();
	void MenuUSESELECTEDRELEASED();
	void InitializeRefs();
	void DebugAction1();
	void DebugAction2();




public:

	EMoveDirections     currMenuMoveDirection;
	FMenuMove	   		delegateMenuMove;
	FMenuUseSelectedPRESSED    delegateMenuUsePRESSED;
	FMenuUseSelectedRELEASED    delegateMenuUseRELEASED;
	FDebugAction1		delegateDebugAction1;
	FDebugAction2		delegateDebugAction2;

	/* ###########################################################
					references
	 ########################################################### */
public:
	UPROPERTY()
		class AMainMenuHUD* refMainMenuHUD;

	/* #########################END############################## */
};
