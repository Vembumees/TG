// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "TG/NPCs/Enemy/BaseEnemy.h"

AEnemyAIController::AEnemyAIController()
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BrainComponent = behaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABaseEnemy* enemyCharacter = Cast<ABaseEnemy>(InPawn);

	if (enemyCharacter && enemyCharacter->behaviorTree)
	{
		blackboardComp->InitializeBlackboard(*enemyCharacter->behaviorTree->BlackboardAsset);

		targetToFollow = blackboardComp->GetKeyID("targetToFollow");
		homeLocation = blackboardComp->GetKeyID("homeLocation");
		targetLocation = blackboardComp->GetKeyID("targetLocation");
		selfActor = blackboardComp->GetKeyID("selfActor");
		paused = blackboardComp->GetKeyID("paused");
		waitTime = blackboardComp->GetKeyID("waitTime");

		behaviorTreeComp->StartTree(*enemyCharacter->behaviorTree);
	}
}
