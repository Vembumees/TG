// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class SG_API IInteractInterface
{
	GENERATED_BODY()
			
public:
	virtual void OnEnterPlayerRadius(AActor* iPlayer) = 0;
	virtual void OnLeavePlayerRadius(AActor* iPlayer) = 0;
	virtual void Interact(AActor* iPlayer) = 0;
};
