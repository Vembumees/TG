// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_SearchTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "TG/Controllers/EnemyAIController.h"
#include "TG/NPCs/Enemy/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"



UMyBTService_SearchTarget::UMyBTService_SearchTarget()
{
	sphereRadius = 3000.0f;
	bAreReferencesSet = false;
}

void UMyBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/** We do this check in the tick node because we are not sure when all of the initialization process will occur, and then protect the recasting with a bool, sloppy, but useful */
	if (bAreReferencesSet == false)
	{
		refEnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
		refBaseEnemy = Cast<ABaseEnemy>(refEnemyAIController->GetPawn());
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(refEnemyAIController->homeLocation, refBaseEnemy->GetActorLocation());

		bAreReferencesSet= true;
	}
	// We want to ignore in the trace all enemy objects 
	TArray<AActor*> l_actorsToIgnore;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), l_actorsToIgnore);

	// The trace will start at current enemy location 
	FVector l_myLocation = refBaseEnemy->GetActorLocation();

	TArray<FHitResult> l_hitResults;

	// Shape of the collision object we are sweeping 
	FCollisionShape l_collisionShape;
	l_collisionShape.ShapeType = ECollisionShape::Sphere;
	l_collisionShape.SetSphere(sphereRadius);

	// And we are looking for pawn type objects, in this case, Rise 
	FCollisionObjectQueryParams l_desiredObjectTypes;
	l_desiredObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	// Adding the actors to ignore 
	FCollisionQueryParams l_traceParams(FName("Trace"), false, l_actorsToIgnore[0]);
	l_traceParams.AddIgnoredActors(l_actorsToIgnore);

	FHitResult l_lineHitResult;
	// Sweep the sphere ignoring enemy alike actors and looking for the pawn 
	if (GetWorld()->SweepMultiByObjectType(l_hitResults, l_myLocation, l_myLocation + FVector(0.0f, 0.0f, 15.0f), FQuat(), l_desiredObjectTypes, l_collisionShape, l_traceParams))
	{
		bool l_correspondenceFound = false;
		// If there were hits, we cycle them 
		for (auto It = l_hitResults.CreateIterator(); It && l_correspondenceFound == false; It++)
		{

			// If some of these hits lead us to the desired target 
			if (GetWorld()->LineTraceSingleByChannel(l_lineHitResult, l_myLocation, l_hitResults[It.GetIndex()].GetActor()->GetActorLocation(), ECollisionChannel::ECC_Pawn, l_traceParams))
			{
				if (l_lineHitResult.GetActor() == l_hitResults[It.GetIndex()].GetActor())
				{
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(refEnemyAIController->targetToFollow, l_lineHitResult.GetActor());
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(refEnemyAIController->targetLocation, l_lineHitResult.GetActor()->GetActorLocation());
					l_correspondenceFound  = true;
				}
				else
				{
					//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BasicEnemyAIReference->TargetToFollow, nullptr);
				}
			}
		}
	}
}
