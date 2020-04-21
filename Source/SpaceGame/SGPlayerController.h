// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

/**
 *  Ok so playercontroller is for stuff we want to control outside of character, like menus and stuff.
 */
UCLASS()
class SPACEGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASGPlayerController();

	UPROPERTY()
		class ASGPlayerPawn* playerPawn;
	
protected:



	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

public:

	void MoveForward(float iVal);
	void MoveRight(float iVal);
	void Interact();
	void Attack();
	
};
