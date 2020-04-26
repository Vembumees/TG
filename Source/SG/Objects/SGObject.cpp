// Fill out your copyright notice in the Description page of Project Settings.


#include "SGObject.h"

// Sets default values
ASGObject::ASGObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("objectMesh"));
	objectMesh->SetupAttachment(RootComponent);
	//todo: init mesh and material from the material in the datatable
	/* ###########################################################
						defaults
	 ########################################################### */

	InteractMessage = InteractMessage;
}

// Called when the game starts or when spawned
void ASGObject::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASGObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASGObject::Interact_Implementation(AActor* iInteracter)
{
	UE_LOG(LogTemp, Warning, TEXT("baah baah %s"));
}

FText ASGObject::GetInteractMessage_Implementation()
{
	return InteractMessage;
}

void ASGObject::IDamage_Implementation(AActor* iAttacker)
{
	
}

