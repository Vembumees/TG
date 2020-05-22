// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Interfaces/CanBeDamaged.h"
#include "BaseEnemy.generated.h"


UENUM(BlueprintType)
enum class EEnemyCharacterState : uint8
{		
	IDLE			UMETA(DisplayName = "Idle"),
	RUN			UMETA(DisplayName = "Run"),
	JUMP			UMETA(DisplayName = "Jump"),
	ATTACK			UMETA(DisplayName = "ATTACK"),
	DEAD			UMETA(DisplayName = "Dead"),
	BLOCK			UMETA(DisplayName = "Block"),
	HIT			UMETA(DisplayName = "Hit"),
	HITHOLD		UMETA(DisplayName = "HitHold"),
	TALK			UMETA(DisplayName = "Talk")
};

UCLASS()
class TG_API ABaseEnemy : public APaperCharacter, public ICanBeDamaged
{
	GENERATED_BODY()
	
public:

	ABaseEnemy();

		UPROPERTY(EditAnywhere, Category = "Talk Widget")
		class UWidgetComponent* healthWidgetComp;


	class UClass* healthWidgetClass;

	UFUNCTION()
		virtual	void Attack();

	UFUNCTION()
		void HandleAttack();

	virtual void BeginPlay() override;

	void InitializeVariables();

	UPROPERTY(VisibleAnywhere)
	EEnemyCharacterState enemyState;

	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
		class UBehaviorTree* behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float damage;
	
	int32 TraceCount;
	float AttackAnimLength;
	float AttackRange;
	float AttackTraceSpread;
	float AttackCooldown;
	bool bDidJustBasicAttack;
	UPROPERTY(VisibleAnywhere)
	AActor* interactedActor;
	void BasicAttackCooldownTimer();

	UFUNCTION()
		void DealDamage();


	virtual void OnGetDamaged(int32 iBaseDamage, AActor* iAttacker) override;

protected:

	virtual void Tick(float DeltaSeconds) override;

	bool bMarkedToDestroy;

	class AEnemyAIController* enemyAI;

	bool bFacingRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* particleSystem;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* audioComponent;

	UFUNCTION()
		void HandleHit();

	UFUNCTION()
		void HandleDestroy();

	UFUNCTION()
		virtual void CheckForDeath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundCue* footstepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundCue* attackedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundCue* attackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundCue* idleSound;



	// The animation to play while running 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* runningAnimation;

	// The animation to play while attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* attackAnimation;


	// The animation to play while being hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* hitAnimation;

	// The animation to play when you die
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* deathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* flickeringDeathAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* idleAnimation;


	/** Called to choose the correct animation to play based on the character's state */
	void UpdateAnimation();

	/** Updates character's basic states */
	void UpdateCharacter();

	virtual void LoadAI();
};
