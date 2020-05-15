// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TG/Enumerations.h"
#include "ExploreController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryMove, EMoveDirections, currInventoryMoveDirection);

UCLASS()
class TG_API AExploreController : public APlayerController
{
	GENERATED_BODY()
public:
	AExploreController();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	//controls
	void BasicAttack();
	void Interact();	
	void MoveRight(float iVal);
	void InitializeRefs();
	void Jump();

	/*Menus*/
	void ToggleIngameMenu();

	void SelectDialog1();
	void SelectDialog2();
	void SelectDialog3();
	void SelectDialog4();

	void InventoryUP();
	void InventoryDOWN();
	void InventoryLEFT();
	void InventoryRIGHT();

	//this is super spaghetti !!
	void SelectDialogByIndex(int32 iIdx);

public:
	EMoveDirections currInventoryMoveDirection;
	FInventoryMove delegateInventoryMove;

	/* ###########################################################
						references
	 ########################################################### */
public:
	UPROPERTY()
	class ATGCharacter* refTGCharacter;

	UPROPERTY()
		class ATGHUD* refHUD;

	/* #########################END############################## */
};
