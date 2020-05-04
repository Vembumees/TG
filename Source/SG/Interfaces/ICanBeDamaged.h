// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICanBeDamaged.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICanBeDamaged : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SG_API IICanBeDamaged
{
	GENERATED_BODY()

public:
	//can add more complexity later
	virtual void OnGetDamaged(float iBaseDamage, AActor* iAttacker) = 0;
};
