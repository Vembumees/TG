// Fill out your copyright notice in the Description page of Project Settings.


#include "TGMasterObject.h"

ATGMasterObject::ATGMasterObject()
{

}

void ATGMasterObject::OnEnterPlayerRadius(AActor* iPlayer)
{
	
}

void ATGMasterObject::OnLeavePlayerRadius(AActor* iPlayer)
{
	
}

void ATGMasterObject::Interact(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void ATGMasterObject::OnGetDamaged(float iBaseDamage, AActor* iAttacker)
{

}

void ATGMasterObject::BeginPlay()
{
	Super::BeginPlay();
}
