// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CloseEnough.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "TG/Controllers/EnemyAIController.h"
#include "TG/TGCharacter.h"

UBTDecorator_CloseEnough::UBTDecorator_CloseEnough()
{
	acceptableDistance = 75.0f;
}

bool UBTDecorator_CloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* enemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyAIController->targetToFollow));
	if (FVector(target->GetActorLocation() - enemyAIController->GetPawn()->GetActorLocation()).Size() >= acceptableDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}
