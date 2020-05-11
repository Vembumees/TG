// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExploreController.generated.h"

/**
 * 
 */
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
