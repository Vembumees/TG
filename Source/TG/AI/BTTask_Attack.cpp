// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "TG/Controllers/EnemyAIController.h"
#include "TG/TGCharacter.h"
#include "TG/NPCs/Enemy/BaseEnemy.h"


UBTTask_Attack::UBTTask_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AEnemyAIController* basicEnemyAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ATGCharacter* refPlayer = Cast<ATGCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(basicEnemyAI->targetToFollow));

	ABaseEnemy* refEnemy = Cast<ABaseEnemy>(basicEnemyAI->GetPawn());

	if (refEnemy != nullptr)
	{
a		if (refPlayer->GetActorLocation().X >= refEnemy->GetActorLocation().X)
			basicEnemyAI->SetControlRotation(FRotator(0.0f, 180.0f, 0.0f));
		else
			basicEnemyAI->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));

		refEnemy->Attack();

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
