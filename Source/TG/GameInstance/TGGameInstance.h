// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TG/Enumerations.h"
#include "Engine/GameInstance.h"
#include "TGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UTGGameInstance : public UGameInstance
{
	GENERATED_BODY()

		UTGGameInstance();

		/*Here we store playerinfo during mapchanges, but also here we manage the gamestates and worldstates
		aka states that store if player is in menu/ingame/duel etc*/


public:
	

	void SetTGGameState(ETGGameState iNewGameState);
	
	ETGGameState GetTGGameState();

private:
	UPROPERTY(VisibleAnywhere)
		ETGGameState TGGameState;
};
