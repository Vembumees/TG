#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TG/Enumerations.h"
#include "Engine/DataTable.h"
#include "MenuItem.generated.h"

USTRUCT(Blueprintable)
struct FMenuItemData
{
	GENERATED_BODY()
		FMenuItemData()
		: ID(0),
		itemName(TEXT("None")),
		itemDescription(TEXT("Default item, use with caution"))
		{}

	UPROPERTY(EditAnywhere)
		int32 ID;
	UPROPERTY(EditAnywhere)
		FString itemName;
	UPROPERTY(EditAnywhere)
		FString itemDescription;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemIcon;
	UPROPERTY(EditAnywhere)
		class UPaperSprite* itemIconPressed;
	//item function
	UPROPERTY(EditAnywhere)
		EMenuItemFunction itemType;
};

USTRUCT(BlueprintType)
struct FItemMenuAllData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		FMenuItemData itemData;
};


UCLASS()
class TG_API AMenuItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/* ###########################################################
						DATA
	 ########################################################### */
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMenuItemData currentMenuItemData;

protected:

	/*idk i feel this is the best and cleanest way to read data from DT, jesus christ, its so short and simple, previous
	method and that's probably still lying around in plenty classes that i took from tutorials and blogs with 
	constructorhelpers is such a long mess and takes multiple useless functions	to create and was so hard to understand 
	and learn (and still is). Frustrating. Just copy this whenever i need DT*/
	void ReadDataTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 dtItemDataRowNumber;


	UPROPERTY()
		TArray<FName> dataTableItemRowNames;
	
public:
	UFUNCTION()
		static AMenuItem* SpawnItem(UWorld* iWorld, int32 iItemIdx);

	/* #########################END############################## */


};
