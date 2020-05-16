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
struct FItemDamage
{

	GENERATED_BODY()

		FItemDamage()
		:
		physical(0),
		fire(0)
		{}

		UPROPERTY(EditAnywhere)
		float physical;
	UPROPERTY(EditAnywhere)
		float fire;
};

USTRUCT(Blueprintable)
struct FItemDefense 
{

	GENERATED_BODY()

		FItemDefense()
		:
		physical(0),
		fire(0)
	{}

		UPROPERTY(EditAnywhere)
		float physical;

	UPROPERTY(EditAnywhere)
		float fire;
};

USTRUCT(Blueprintable)
struct FItemData
{

	GENERATED_BODY()

		FItemData()
		: ID(0),
		itemName(FName(TEXT("NULL"))),
		itemRarity(EItemRarity::COMMON),
		itemType(EItemType::TOKEN),
		itemDescription(TEXT("Default item, use with caution")) 
		{}

		UPROPERTY(EditAnywhere)
		int32 ID;

	UPROPERTY(EditAnywhere)
		FName itemName;

	UPROPERTY(EditAnywhere)
		EItemRarity itemRarity;

	UPROPERTY(EditAnywhere)
		EItemType itemType;

	UPROPERTY(EditAnywhere)
		FString itemDescription;

	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemIcon;

	UPROPERTY(EditAnywhere)
		class UPaperFlipbook* itemWorldFlipbook;

	UPROPERTY(EditAnywhere)
		FItemDamage itemDamage;

	UPROPERTY(EditAnywhere)
		FItemDefense itemDefense;
};

USTRUCT(BlueprintType)
struct FItemAllData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		FItemData itemData;
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
	UPROPERTY(EditDefaultsOnly, Category = AData)
		bool bIsCollectable = true;

	UPROPERTY(EditDefaultsOnly, Category = AData)
		int32 ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AItem)
		class USceneComponent* itemRootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AItem)
		class UPaperFlipbookComponent* SpriteComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AItem)
		class UBoxComponent* collisionComp;

public:



	void SetFlipbook(UPaperFlipbook* iFlipBook);

	bool IsCollectable() const { return bIsCollectable; }

	FORCEINLINE int32 GetID() const { return ID; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/* ###########################################################
						DATA
	 ########################################################### */
public:
	FItemData GetCurrentItemData() { return currentItemData; }
	void SetDataTableItemDataRowNames();
protected:

	void StartInitializeTimer();
	void InitializeDelayed();
	void InitializeDataTableInfo();
	void PassDataFromTableToObjectVariables();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		int32 DTItemDataRowNumber;

	UPROPERTY()
		class UDataTable* DataTableItemData;
	UPROPERTY()
		TArray<FName> DataTableItemRowNames;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FItemData currentItemData;

	 /* #########################END############################## */

};