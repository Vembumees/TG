// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "TG/Projectiles/Projectile.h"
#include "BrainComponent.h"
#include "TG/Controllers/EnemyAIController.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ARangedEnemy::ARangedEnemy()
{
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	LoadAI();
}

void ARangedEnemy::Attack()
{
	Super::Attack();

	FVector location = this->GetActorLocation();
	if (bFacingRight)
	{
		location += FVector(75.0f, 0.0f, 30.0f);
	}
	else
	{
		location += FVector(-75.0f, 0.0f, 30.0f);
	}		
	FActorSpawnParameters spawnInfo;
	GetWorld()->SpawnActor<AProjectile>(rangedProjectile, location, this->GetActorRotation(), spawnInfo);
}

void ARangedEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARangedEnemy::LoadAI()
{
	Super::LoadAI();
}

void ARangedEnemy::CheckForDeath()
{
	Super::CheckForDeath();

	//this is custom for thsi character's current death animation spritesheet
	FVector loc = GetActorLocation();
	loc.Z += 140;
	this->SetActorRelativeLocation(loc);
}
