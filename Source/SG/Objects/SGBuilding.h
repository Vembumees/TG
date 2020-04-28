// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SG/Objects/SGObject.h"
#include "SGBuilding.generated.h"

/**
 * 
 */
UCLASS()
class SG_API ASGBuilding : public ASGObject
{
	GENERATED_BODY()

		ASGBuilding();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;


};
