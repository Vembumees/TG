// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TG/Enumerations.h"
#include "Engine/DataTable.h"
#include "TG/Interfaces/Interact.h"
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
	TOME					UMETA(DisplayName = "Card"),
	TOKEN					UMETA(DisplayName = "Token"),
	ARTIFACT				UMETA(DisplayName = "Artifact"),
	SOUL					UMETA(DisplayName = "Soul"),
	MYSTICAL				UMETA(DisplayName = "Mystical"),
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
struct FItemAbility
{

	GENERATED_BODY()

		FItemAbility()
		:
		abilityType(EAbilityType::NONE),
		magicType(ECardMagicTypes::NONE),
		power(0)
	{}

	UPROPERTY(EditAnywhere)
		EAbilityType abilityType;

	UPROPERTY(EditAnywhere)
		ECardMagicTypes magicType;

	UPROPERTY(EditAnywhere)
		int32 power;
	
};

USTRUCT(Blueprintable)
struct FItemData
{

	GENERATED_BODY()

		FItemData()
		: ID(0),
		bIsOnCooldown(false),
		bIsConsumedOnUse(false),
		itemCooldown(5.0),
		itemName(FText(FText::FromString("NONE"))),
		itemRarity(EItemRarity::COMMON),
		itemType(EItemType::TOKEN),
		itemDescription(TEXT("Default item, use with caution")) 
		{}

		UPROPERTY(EditAnywhere)
		int32 ID;

		UPROPERTY()
			bool bIsOnCooldown; //for gameplay logic

		UPROPERTY(EditAnywhere)
			bool bIsConsumedOnUse;

		UPROPERTY(EditAnywhere)
			float itemCooldown;

	UPROPERTY(EditAnywhere)
		FText itemName;

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
		FItemAbility itemAbility;

	UPROPERTY(EditAnywhere)
		FItemDamage itemDamage;
};

USTRUCT(BlueprintType)
struct FItemAllData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		FItemData itemData;
};

UCLASS()
class TG_API AItem : public AActor, public IInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();


	virtual void OnConstruction(const FTransform& Transform) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;


	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;


	virtual void Interact(AActor* iPlayer) override;

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

	class UBoxComponent* GetCollisionComp() { return collisionComp; }



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


public:

	/*removed the getter and set this to public atm, because had some errors because of them and want to avoid
	passing around way too many struct copies*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AData)
		FItemData currentItemData;

	 /* #########################END############################## */


	/* ###########################################################
						ITEM CREATION STUFF
	 ########################################################### */
	/*static function here that spawns an item at requested location, at least atm I don't think that 
	  I need a separate item manager specifically for this, I can just call this function to spawn the item
	  and store the reference in the class that spawns it - the class's inventory component
	  */

	  /*iWorld - worldcontext,
		iLocation - where we want to spawn the item
	    iItemIdx - index number of the item data in item datatable, errorprone but simple
		ibAreWeAddingToInventory - if we spawn item to inventory we want to set the parameters of item for that*/
	UFUNCTION()
	static AItem* SpawnItem(UWorld* iWorld, FVector iLocation, int32 iItemIdx, bool ibAreWeAddingToInventory);


	 /* #########################END############################## */



	/* ###########################################################
						Game Functionality
	 ########################################################### */
public:


	 /* #########################END############################## */
};