// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGGameMode.generated.h"

UCLASS(MinimalAPI)
class ASGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGGameMode();


public:
	/* ###########################################################
				DATA
########################################################### */

	UPROPERTY()
		class UDataTable* DTObjectData;

	UPROPERTY()
		TArray<FName> DTObjectDataRowNames;



	
	

protected:
	virtual void BeginPlay() override;
	void SetDTObjectDataRowNames();
};



