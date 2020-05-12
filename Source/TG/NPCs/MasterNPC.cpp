// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterNPC.h"
#include "TG/TG.h"
#include "PaperFlipbookComponent.h"

AMasterNPC::AMasterNPC()
{
	dialogueAlert= CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("dialogueAlert"));
	dialogueAlert->SetupAttachment(RootComponent);
	dialogueAlert->SetRelativeLocation(FVector(30,0,150));
	dialogueAlert->SetRelativeScale3D(FVector(3,3,3));
	dialogueAlert->SetVisibility(false);

	GetSprite()->SetRelativeScale3D(TG_SPRITE_SCALE);

}

void AMasterNPC::OnEnterPlayerRadius(AActor* iPlayer)
{
	dialogueAlert->SetVisibility(true);
	RotateTowardsPlayer();

	
}

void AMasterNPC::OnLeavePlayerRadius(AActor* iPlayer)
{
	dialogueAlert->SetVisibility(false);

}

void AMasterNPC::Interact(AActor* iPlayer)
{

}

void AMasterNPC::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterNPC::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//keeps the actor at the right position in 2d in editor
	FTransform trans = this->GetActorTransform();
	FVector loc = trans.GetLocation();
	loc.Y = -1; //so it wouldn't clip
	trans.SetLocation(loc);
	this->SetActorTransform(trans);
}

void AMasterNPC::RotateTowardsPlayer()
{
	FRotator playerRot = iPlayer->GetActorRotation();
	if (playerRot.Yaw < 0)
	{
		GetSprite()->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else
	{
		GetSprite()->SetRelativeRotation(FRotator(0, -180.0f, 0));
	}

}
