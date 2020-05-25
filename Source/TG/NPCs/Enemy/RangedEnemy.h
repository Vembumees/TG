// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TG/NPCs/Enemy/BaseEnemy.h"
#include "RangedEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TG_API ARangedEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
		ARangedEnemy();
		
		
		
		



		virtual void Attack() override;

protected: 
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> rangedProjectile;

	virtual void LoadAI() override;


	virtual void CheckForDeath() override;

};
