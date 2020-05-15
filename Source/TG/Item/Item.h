// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

/*Items are atm just set invisible when looted and their pointers stored in the character's 
inventoryComponent, so careful with that, I probably have to store each item we are carrying
so they come with the character when we change levels, or a global place to store all the items
or something*/

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	COMMON						UMETA(DisplayName = "Common"),
	MAGIC						UMETA(DisplayName = "Magic"),
	ULTRA						UMETA(DisplayName = "Ultra"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	CARD						UMETA(DisplayName = "Card"),
	TOKEN						UMETA(DisplayName = "Token"),
	CURRENCY					UMETA(DisplayName = "Currency"),
};

USTRUCT(Blueprintable)
struct FItemDamage : public FTableRowBase {

	GENERATED_BODY()

		FItemDamage()
		:
		physical(0),
		fire(0)
		{}

		UPROPERTY(VisibleAnywhere)
		float physical;
	UPROPERTY(VisibleAnywhere)
		float fire;
};

USTRUCT(Blueprintable)
struct FItemDefense : public FTableRowBase {

	GENERATED_BODY()

		FItemDefense()
		:
		physical(0),
		fire(0)
	{}

		UPROPERTY(VisibleAnywhere)
		float physical;

	UPROPERTY(VisibleAnywhere)
		float fire;
};

USTRUCT(Blueprintable)
struct FItemData : public FTableRowBase {

	GENERATED_BODY()

		FItemData()
		: ID(0),
		itemName(FName(TEXT("NULL"))),
		itemRarity(EItemRarity::COMMON),
		itemType(EItemType::TOKEN),
		itemDescription(TEXT("Default item, use with caution")) 
		{}

		UPROPERTY(VisibleAnywhere)
		int32 ID;

	UPROPERTY(VisibleAnywhere)
		FName itemName;

	UPROPERTY(VisibleAnywhere)
		EItemRarity itemRarity;

	UPROPERTY(VisibleAnywhere)
		EItemType itemType;

	UPROPERTY(VisibleAnywhere)
		FString itemDescription;

	UPROPERTY(VisibleAnywhere)
		TAssetPtr<class UPaperSprite> itemIcon;

	UPROPERTY(VisibleAnywhere)
		TAssetPtr<class UPaperFlipbook> itemWorldFlipbook;

	UPROPERTY(VisibleAnywhere)
		FItemDamage itemDamage;

	UPROPERTY(VisibleAnywhere)
		FItemDefense itemDefense;
};

UCLASS()
class TG_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();


	virtual void OnConstruction(const FTransform& Transform) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		bool bIsCollectable = true;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int32 ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class USceneComponent* itemRootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class UPaperFlipbookComponent* worldFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AMesh)
		class UBoxComponent* collisionComp;

public:



	void SetFlipbook(UPaperFlipbook* iFlipBook);

	bool IsCollectable() const { return bIsCollectable; }

	FORCEINLINE int32 GetID() const { return ID; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};