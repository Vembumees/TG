// Fill out your copyright notice in the Description page of Project Settings.


#include "SGObject.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/DataTable.h"
#include "SG/SGGameMode.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"

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

	this->m_interactMessage = FText::FromString("None");
	initializeTimer = 1.0f;
}

// Called when the game starts or when spawned
void ASGObject::BeginPlay()
{
	Super::BeginPlay();	

	InitNecessaryRefs();

	// triggers InitializeDelayed() after set time
	StartInitTimer();
	
}

// Called every frame
void ASGObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void ASGObject::OnEnterPlayerRadius(AActor* iPlayer)
{

}

void ASGObject::OnLeavePlayerRadius(AActor* iPlayer)
{
	
}

void ASGObject::Interact(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("baah baah %s"), *m_interactMessage.ToString());
}

void ASGObject::OnGetDamaged(float iBaseDamage, AActor* iAttacker)
{
	
}

void ASGObject::InitializeComponentsFromData()
{
	objectMesh->SetStaticMesh(ObjectsCurrentStats.staticMesh);
	objectMesh->SetMaterial(0, ObjectsCurrentStats.material);
}

void ASGObject::StartInitTimer()
{
	
		FTimerHandle DelayInitData;
		FTimerDelegate DelayInitDataDel;
		DelayInitDataDel.BindUFunction(this, FName("InitializeDelayed"));
		GetWorldTimerManager().SetTimer(DelayInitData, DelayInitDataDel, initializeTimer, false);
}

void ASGObject::InitializeDelayed()
{
	InitDTInfo();
	//after we get Mesh/material from DT we put it on the object
	InitializeComponentsFromData();
}

void ASGObject::InitDTInfo()
{
	/*Take Object data from specified row*/
	if (refGameMode != nullptr && refGameMode->DTObjectData != nullptr)
	{
		FObjectData* ObjectData = refGameMode->DTObjectData->FindRow<FObjectData>(
			refGameMode->DTObjectDataRowNames[DTObjectStatsRowNumber], "SGObject DTObjectStats", true);
		if (ObjectData != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ObjectData LOADED SUCCESSFULLY."));
			ObjectsCurrentStats = ObjectData->objStats;

			//update interactMessage
			m_interactMessage = ObjectsCurrentStats.interactMessage;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ObjectData load FAILED"));
		}
	}

	
}

void ASGObject::InitNecessaryRefs()
{
	refGameMode = Cast<ASGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

