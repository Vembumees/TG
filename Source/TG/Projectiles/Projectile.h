// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.generated.h"

UCLASS()
class TG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* projectileMovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPaperFlipbookComponent* spriteComp;

protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void SetHomingDistance(float iDistance);

	void StopHoming();

protected:

	//animation when projectile is moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* projectileMoveAnim;

	//animation when projectile collides
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* projectileCollideAnim;

private:
	class ATGCharacter* refTGCharacter;


};
