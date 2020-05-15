// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"

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

void AItem::SetFlipbook(UPaperFlipbook* iFlipBook)
{
	worldFlipbook->SetFlipbook(iFlipBook);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

