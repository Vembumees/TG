// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "TG/TGCharacter.h"
#include "TG/Components/InventoryComponent.h"

// Sets default values
AItem::AItem()
{
	itemRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("itemRootComp "));
	this->RootComponent = itemRootComp;

	worldFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComp"));
	worldFlipbook->SetRelativeScale3D(FVector(3, 3, 3));
	worldFlipbook->SetupAttachment(itemRootComp);

	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("collisionComp "));
	collisionComp->SetupAttachment(itemRootComp);
	collisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
}


void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//keeps the actor at the right position in 2d in editor
	FTransform trans = this->GetActorTransform();
	FVector loc = trans.GetLocation();
	loc.Y = -1; //so it wouldn't clip
	trans.SetLocation(loc);
	this->SetActorTransform(trans);
}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("AItem::NotifyActorBeginOverlap"));
	ATGCharacter* player = Cast<ATGCharacter>(OtherActor);
	if (player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AItem::NotifyActorBeginOverlap cast fail"));
		return;
	}
	
	if (player->GetInventoryComponent()->AddItemToInventory(this))
	{
		UE_LOG(LogTemp, Warning, TEXT("AItem::NotifyActorBeginOverlap - adding item successful"));
		collisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->SetActorHiddenInGame(true); //test
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AItem::NotifyActorBeginOverlap - adding item fail"));
	}
}

void AItem::SetFlipbook(UPaperFlipbook* iFlipBook)
{
	worldFlipbook->SetFlipbook(iFlipBook);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

