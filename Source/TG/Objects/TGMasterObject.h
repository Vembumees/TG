// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "TG/Interfaces/Interact.h"
#include "TG/Interfaces/CanBeDamaged.h"
#include "TGMasterObject.generated.h"

/**
 * 
 */
UCLASS()
class TG_API ATGMasterObject : public APaperSpriteActor, public IInteract, public ICanBeDamaged
{
	GENERATED_BODY()

public:
		ATGMasterObject();

		/* ###########################################################
						Interface functions
	 ########################################################### */
		virtual void OnEnterPlayerRadius(AActor* iPlayer) override;
		virtual void OnLeavePlayerRadius(AActor* iPlayer) override;
		virtual void Interact(AActor* iPlayer) override;
		virtual void OnGetDamaged(float iBaseDamage, AActor* iAttacker) override;

	 /* #########################END############################## */


protected:
	virtual void BeginPlay() override;

};
