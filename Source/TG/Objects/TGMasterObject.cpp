// Fill out your copyright notice in the Description page of Project Settings.


#include "TGMasterObject.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"


ATGMasterObject::ATGMasterObject()
{
	/* ###########################################################
							DATA
########################################################### */
/*load object stats datatable automatically, datatable values are in beginplay*/
	static ConstructorHelpers::FObjectFinder<UDataTable> ObjectStatsDTObject(TEXT("DataTable'/Game/TG/BP/Data/DT_ObjectData.DT_ObjectData'"));
	if (ObjectStatsDTObject.Succeeded())
	{

		//Use CharacterStatsDataTable to access the table data
		DataTableObjectData = ObjectStatsDTObject.Object;
	}

	objectRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	this->RootComponent = objectRootComp;


	boxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollisionComp"));
	boxCollisionComp->AttachToComponent(objectRootComp, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollisionComp->SetCollisionProfileName("WorldDynamic");
	boxCollisionComp->SetConstraintMode(EDOFMode::XZPlane);
	/*	GetCapsuleComponent()->SetConstraintMode(EDOFMode::XZPlane);*/


	SpriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComp"));
	SpriteComp->AttachToComponent(objectRootComp, FAttachmentTransformRules::KeepRelativeTransform);

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComp->SetupAttachment(objectRootComp);
	

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

void ATGMasterObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//keeps the actor at the right position in 2d in editor
	FTransform trans = this->GetActorTransform();
	FVector loc = trans.GetLocation();
	loc.Y = -1; //so it wouldn't clip
	trans.SetLocation(loc);
	this->SetActorTransform(trans);
}

void ATGMasterObject::BeginPlay()
{
	Super::BeginPlay();
	StartInitializeTimer();
	InitializeReferences();
	SetDataTableObjectDataRowNames();
}

void ATGMasterObject::PassDataFromTableToObjectVariables()
{
	this->SpriteComp->SetFlipbook(currentBasicAnimations.ObjectIdleAnimation);

}

void ATGMasterObject::StartInitializeTimer()
{
	FTimerHandle TGMasterObjectInitializeTimer;
	GetWorld()->GetTimerManager().SetTimer(TGMasterObjectInitializeTimer, this, &ATGMasterObject::InitializeDelayed,
		initializeTimer, false);
}

void ATGMasterObject::InitializeDelayed()
{
	InitializeDataTableInfo();
	PassDataFromTableToObjectVariables();
}

void ATGMasterObject::InitializeDataTableInfo()
{

	FObjectData* ObjectData = DataTableObjectData->FindRow<FObjectData>(
		DataTableObjectRowNames[DTObjectStatsRowNumber], "SGObject DTObjectStats", true);
	if (ObjectData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectData LOADED SUCCESSFULLY."));
		currentBasicStats = ObjectData->objectStats;
		currentBasicAnimations = ObjectData->objectBasicAnimations;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectData load FAILED"));
	}
}


void ATGMasterObject::InitializeReferences()
{

}

void ATGMasterObject::SetDataTableObjectDataRowNames()
{
	if (DataTableObjectData != nullptr)
	{
		DataTableObjectRowNames = DataTableObjectData->GetRowNames();
	}
}
