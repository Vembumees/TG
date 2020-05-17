// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TG/TGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("boxCollision"));
	sphereCollision->SetupAttachment(RootComponent);
	sphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	spriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("spriteComp"));
	spriteComp->SetupAttachment(RootComponent);
	spriteComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	spriteComp->SetFlipbook(projectileMoveAnim);


	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMovementComp"));
	projectileMovementComp->ProjectileGravityScale = 0.0f;
	projectileMovementComp->InitialSpeed = 600;
	projectileMovementComp->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	spriteComp->SetFlipbook(projectileCollideAnim);
	sphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	this->SetLifeSpan(0.5);
	
}
