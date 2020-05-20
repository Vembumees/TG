// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

		AEnemyAIController();
	
public:
	UPROPERTY(transient)
		class UBlackboardComponent* blackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* behaviorTreeComp;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp; }
	virtual void OnPossess(APawn* InPawn) override;

	uint8 targetToFollow;
	uint8 homeLocation;
	uint8 targetLocation;
	uint8 selfActor;
	uint8 paused;
	uint8 waitTime;
};
