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
	/* ###########################################################
					DATA
	########################################################### */
	/*load object stats datatable automatically, datatable values are in beginplay*/
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataDTObject(TEXT("DataTable'/Game/TG/BP/Data/DT_ItemData.DT_ItemData'"));
	if (ItemDataDTObject.Succeeded())
	{

		//Use CharacterStatsDataTable to access the table data
		DataTableItemData = ItemDataDTObject.Object;
	}
	/* #########################END############################## */

	itemRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("itemRootComp "));
	this->RootComponent = itemRootComp;

	SpriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComp"));
	SpriteComp->SetRelativeScale3D(FVector(3, 3, 3));
	SpriteComp->SetupAttachment(itemRootComp);

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

}

void AItem::OnEnterPlayerRadius(AActor* iPlayer)
{
	//maybe make item glow here? or play sound TODO
}

void AItem::OnLeavePlayerRadius(AActor* iPlayer)
{
	
}

void AItem::Interact(AActor* iPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("AItem::NotifyActorBeginOverlap"));
	ATGCharacter* player = Cast<ATGCharacter>(iPlayer);
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
	SpriteComp->SetFlipbook(iFlipBook);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	StartInitializeTimer();
	SetDataTableItemDataRowNames();	
}


void AItem::SetDataTableItemDataRowNames()
{
	if (DataTableItemData != nullptr)
	{
		DataTableItemRowNames = DataTableItemData->GetRowNames();
	}
}

void AItem::StartInitializeTimer()
{
	FTimerHandle itemInitializeTimer;
	GetWorld()->GetTimerManager().SetTimer(itemInitializeTimer, this, &AItem::InitializeDelayed, 0.1, false);
}

void AItem::InitializeDelayed()
{
	InitializeDataTableInfo();
	PassDataFromTableToObjectVariables();
}

void AItem::InitializeDataTableInfo()
{
	FItemAllData* itemALLData = DataTableItemData->FindRow<FItemAllData>(
		DataTableItemRowNames[DTItemDataRowNumber], "AItem DTItemData", true);
	if (itemALLData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemData LOADED SUCCESSFULLY."));
		currentItemData = itemALLData->itemData;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ItemData load FAILED"));
	}
}

void AItem::PassDataFromTableToObjectVariables()
{
	this->SpriteComp->SetFlipbook(currentItemData.itemWorldFlipbook);
}


