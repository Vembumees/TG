// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "TG/TG.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "TG/Controllers/EnemyAIController.h"

ABaseEnemy::ABaseEnemy()
{
	health = 1.0f;
	currentHealth = health;
	AttackCooldown = 0.5;
	TraceCount = 15;
	AttackAnimLength = 1.0f;
	AttackRange = 300.0f;
	AttackTraceSpread = 0.5f;
	bDidJustBasicAttack = false;
	bMarkedToDestroy = false;
	enemyState = EEnemyCharacterState::IDLE;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->bAutoActivate = false;
	audioComponent->SetupAttachment(RootComponent);

	

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	GetSprite()->SetRelativeLocation(FVector(0,0,0));
	GetSprite()->SetRelativeScale3D(TG_SPRITE_SCALE);

	healthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("health widget"));
	healthWidgetComp->SetupAttachment(RootComponent);
	healthWidgetComp->SetVisibility(true);
	healthWidgetComp->SetWidgetClass(healthWidgetClass);
	healthWidgetComp->SetWorldScale3D(FVector(0.5f));
	healthWidgetComp->SetRelativeLocation(FVector(100.0f, 0.0f, -230.0f));
	healthWidgetComp->SetAbsolute(false, true, false);
	healthWidgetComp->SetRelativeRotation(FQuat(FRotator(0.0f, 90.0f, 0.0f)));

	LoadAI();
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitializeVariables();
}

void ABaseEnemy::InitializeVariables()
{
	enemyAI = Cast<AEnemyAIController>(GetController());
	enemyAI->GetBlackboardComp()->SetValue<UBlackboardKeyType_Float>(enemyAI->waitTime, 1.0f);
}

void ABaseEnemy::BasicAttackCooldownTimer()
{
	bDidJustBasicAttack = true;
}

void ABaseEnemy::DealDamage()
{
	FVector Start;
	FVector End;
	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;
	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);
	Start = PlayerEyesLoc;
	/*End = Start + (PlayerEyesRot.Vector() * InteractDistance);*/ //normal
	for (int i = 0; i < TraceCount; i++)
	{
		End = Start + (FMath::VRandCone(PlayerEyesRot.Vector(), AttackTraceSpread, AttackTraceSpread)) * AttackRange; //with spread
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 3.0f);
		FHitResult HitResult = FHitResult(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, TraceParams))
		{
			if (HitResult.GetActor() != nullptr)
			{
				if (HitResult.GetActor()->GetClass()->ImplementsInterface(UCanBeDamaged::StaticClass()) &&
					!bDidJustBasicAttack)
				{
					//if we did successful interact with interface we need to make sure it only did it once
					bDidJustBasicAttack = true;
					FTimerHandle justBasicAttackedTimer;
					GetWorld()->GetTimerManager().SetTimer(justBasicAttackedTimer, this, &ABaseEnemy::BasicAttackCooldownTimer, AttackCooldown, false);

					//play success sound?

					//since its here not above scope it will only show actors with the interact interface only 
					interactedActor = HitResult.GetActor();

					ICanBeDamaged* dmgInterface = Cast<ICanBeDamaged>(interactedActor);
					if (dmgInterface != nullptr)
					{
						dmgInterface->OnGetDamaged(damage, this);
					}
				}
			}
		}
	}
}

void ABaseEnemy::OnGetDamaged(int32 iBaseDamage, AActor* iAttacker)
{

	//play sound

	//play on get hit animation

	//move character a little in opposite direction


	//atm have no get hit anim need to make it
// 	float TimelineLength = hitAnimation->GetNumFrames() / (float)hitAnimation->GetFramesPerSecond();
// 	FTimerHandle TimerHandle;
// 	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::HandleHit, TimelineLength - 0.05f * TimelineLength, false);


	/*enemyState = EEnemyCharacterState::HIT;*/
	this->currentHealth -= iBaseDamage;
	enemyAI->GetBrainComponent()->StopLogic("Hit");
	UE_LOG(LogTemp, Warning, TEXT("enemy damaged, %i health remaining."), currentHealth);
	CheckForDeath();
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();

	enemyAI->GetBlackboardComp()->SetValue<UBlackboardKeyType_Float>(enemyAI->waitTime, FMath::RandRange(1.0f, 3.0f));
}



void ABaseEnemy::Attack()
{
	if (enemyState != EEnemyCharacterState::DEAD)
	{
		//play sound

		float TimelineLength = attackAnimation->GetNumFrames() / (float)attackAnimation->GetFramesPerSecond();
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::HandleAttack, TimelineLength - 0.05f * TimelineLength, false);
		
		enemyAI->GetBlackboardComp()->SetValue<UBlackboardKeyType_Bool>(enemyAI->paused, true);
		enemyState = EEnemyCharacterState::ATTACK;
	}
}

void ABaseEnemy::HandleAttack()
{
	if (enemyState != EEnemyCharacterState::DEAD && enemyState != EEnemyCharacterState::HIT)
	{
		enemyState = EEnemyCharacterState::IDLE;
		enemyAI->GetBlackboardComp()->SetValue<UBlackboardKeyType_Bool>(enemyAI->paused, false);
	}
}

void ABaseEnemy::HandleHit()
{
	if (currentHealth >= 0.0f && enemyState != EEnemyCharacterState::DEAD)
	{
		enemyState = EEnemyCharacterState::IDLE;
		enemyAI->GetBrainComponent()->RestartLogic();
		enemyAI->GetBlackboardComp()->SetValue<UBlackboardKeyType_Bool>(enemyAI->paused, false);
	}
}

void ABaseEnemy::HandleDestroy()
{
	Destroy();
}

void ABaseEnemy::CheckForDeath()
{
	if (currentHealth <= 0)
	{
		this->SetActorEnableCollision(false);
		//play death animation and in 10 seconds fall through the ground and destroy self
		enemyState = EEnemyCharacterState::DEAD;
		UpdateAnimation();

		//give xp & drop loot?

		enemyAI->GetBrainComponent()->StopLogic("Dead");
		GetController()->UnPossess();
		bMarkedToDestroy = true;
		float timelineLength = deathAnimation->GetNumFrames() / (float)deathAnimation->GetFramesPerSecond();
		FTimerHandle baseEnemyTimerHandle;
		GetWorldTimerManager().SetTimer(baseEnemyTimerHandle, this,
			&ABaseEnemy::HandleDestroy, timelineLength - (0.05f * timelineLength), false);

	}
}

void ABaseEnemy::UpdateAnimation()
{
	UPaperFlipbook* desiredAnimation = nullptr;
	switch (enemyState)
	{
	case EEnemyCharacterState::IDLE:
		desiredAnimation = idleAnimation;
		break;
	case EEnemyCharacterState::RUN:
		desiredAnimation = runningAnimation;
		break;
	case EEnemyCharacterState::JUMP:
		
		break;
	case EEnemyCharacterState::ATTACK:
		desiredAnimation = attackAnimation;
		break;
	case EEnemyCharacterState::DEAD:
		if (bMarkedToDestroy)
		{
			desiredAnimation = flickeringDeathAnimation;
		}
		else
		{
			desiredAnimation = deathAnimation;
		}
		
		break;
	case EEnemyCharacterState::BLOCK:
		
		break;
	case EEnemyCharacterState::HIT:
		desiredAnimation = hitAnimation;
		break;
	case EEnemyCharacterState::HITHOLD:
		
		break;
	case EEnemyCharacterState::TALK:

		break;
	}


	if (GetSprite()->GetFlipbook() != desiredAnimation)
	{
		GetSprite()->SetFlipbook(desiredAnimation);
	}
}

void ABaseEnemy::UpdateCharacter()
{
	UpdateAnimation();


	const FVector playerVelocity = GetVelocity();
	float travelDirection = playerVelocity.X;

	const float playerSpeedSqr = playerVelocity.SizeSquared();

	const UEnum* ptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyCharacterState"), true);
	auto index = ptr->GetIndexByValue((uint8)enemyState);

	if (enemyState == EEnemyCharacterState::RUN || enemyState == EEnemyCharacterState::IDLE)
	{
		if (playerSpeedSqr > 0.0f)
		{
			enemyState = EEnemyCharacterState::RUN;
		}
		else
		{
			enemyState = EEnemyCharacterState::IDLE;
		}
	}

	if (this->GetActorRotation().Yaw != 0.0f)
	{
		bFacingRight = false;
	}
	else
	{
		bFacingRight = true;
	}

	//set the rotation so that the character faces his direction of travel
	if (Controller != nullptr)
	{
		if (travelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

}


void ABaseEnemy::LoadAI()
{
	this->AIControllerClass = AEnemyAIController::StaticClass();
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

