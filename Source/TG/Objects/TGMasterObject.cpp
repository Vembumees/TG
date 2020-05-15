// Fill out your copyright notice in the Description page of Project Settings.


#include "TGMasterObject.h"
#include "TG/TG.h"
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
	static ConstructorHelpers::FObjectFinder<UDataTable> ObjectDataDTObject(TEXT("DataTable'/Game/TG/BP/Data/DT_ObjectData.DT_ObjectData'"));
	if (ObjectDataDTObject.Succeeded())
	{

		//Use CharacterStatsDataTable to access the table data
		DataTableObjectData = ObjectDataDTObject.Object;
	}
	/* #########################END############################## */

	objectRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	this->RootComponent = objectRootComp;


	boxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollisionComp"));
	boxCollisionComp->AttachToComponent(objectRootComp, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollisionComp->SetCollisionProfileName("WorldDynamic");
	boxCollisionComp->SetConstraintMode(EDOFMode::XZPlane);
	/*	GetCapsuleComponent()->SetConstraintMode(EDOFMode::XZPlane);*/


	SpriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComp"));
	SpriteComp->AttachToComponent(objectRootComp, FAttachmentTransformRules::KeepRelativeTransform);
	SpriteComp->SetRelativeScale3D(TG_SPRITE_SCALE);

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComp->SetupAttachment(objectRootComp);






	/* ###########################################################
						DEFAULT VALUES	
	 ########################################################### */
		initializeTimer = 0.3f;
		objectDeathTimer = 5.0f;
		
	 /* #########################END############################## */
	

}

void ATGMasterObject::OnEnterPlayerRadius(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter"));
}

void ATGMasterObject::OnLeavePlayerRadius(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Leave"));
}

void ATGMasterObject::Interact(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void ATGMasterObject::OnGetDamaged(int32 iBaseDamage, AActor* iAttacker)
{
	if (iBaseDamage >= 0 && !currentBasicStats.bIsDestroyed)
	{
		FlickerOndamageTakenBadMethod();
		currentBasicStats.currentHealth -= iBaseDamage;
		UE_LOG(LogTemp, Warning, TEXT("Object damaged, %i health remaining."), currentBasicStats.currentHealth);
		if (currentBasicStats.currentHealth <= 0)
		{
			currentBasicStats.bIsDestroyed = true;
			//play death animation and in 10 seconds fall through the ground and destroy self 
			this->SpriteComp->SetLooping(false);
			/*this->SpriteComp->SetFlipbook(currentBasicAnimations.ObjectDestroyedAnimation); !! atm dont have anim*/ 
			this->SpriteComp->SetSpriteColor(FLinearColor::Red);
			this->boxCollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			//give xp & drop loot?
			
			//here we can add some effect in future for disappearing corpses

			//destroys the object in set time
			this->SetLifeSpan(objectDeathTimer);

		}
	}
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
	//pass the sprite
	this->SpriteComp->SetFlipbook(currentBasicAnimations.ObjectIdleAnimation);

	//pass stats
	

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

	FObjectData* objectData = DataTableObjectData->FindRow<FObjectData>(
		DataTableObjectRowNames[DTObjectStatsRowNumber], "SGObject DTObjectStats", true);
	if (objectData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectData LOADED SUCCESSFULLY."));
		currentBasicStats = objectData->objectStats;
		currentBasicAnimations = objectData->objectBasicAnimations;
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

void ATGMasterObject::FlickerOndamageTakenBadMethod()
{
	//this is some incredibly horrendous code but i couldnt quickly figure out a way to do this in this crappy
	//unsupported paper2d without drawing the sprites manually, maybe will find or figure something out in future !!
	// or just not do the flashing xD

	//or just make 2-3 sprites for object, each more broken. Not like most of them will be animated anyway, just sprites

	//maybe could just do a shake with lerp or something (that requires tick tho) or manually shake the object
	//basic gamefeel not rly priority tho atm
	FTimerHandle DmgTakenFlickerSetFlashColor;
	FTimerHandle DmgTakenFlickerSetNormal;
	FTimerHandle DmgTakenFlickerSetFlashColor2;
	FTimerHandle DmgTakenFlickerSetNormal2;

	GetWorld()->GetTimerManager().SetTimer(
		DmgTakenFlickerSetFlashColor, this,&ATGMasterObject::FlickerSetFlashColor, 0.1);
	GetWorld()->GetTimerManager().SetTimer(
		DmgTakenFlickerSetNormal, this, &ATGMasterObject::FlickerSetFlashNormal, 0.2);
}

void ATGMasterObject::FlickerSetFlashColor()
{
	this->SpriteComp->SetSpriteColor(flickerColor);
}

void ATGMasterObject::FlickerSetFlashNormal()
{
	this->SpriteComp->SetSpriteColor(FLinearColor::White);
}

