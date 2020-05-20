// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_SearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UMyBTService_SearchTarget : public UBTService
{
	GENERATED_BODY()
	
		UPROPERTY(EditInstanceOnly, Category = "Trace")
		float sphereRadius;

	class AEnemyAIController* refEnemyAIController;
	class ABaseEnemy* refBaseEnemy;
	bool bAreReferencesSet;

public:

	UMyBTService_SearchTarget();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
