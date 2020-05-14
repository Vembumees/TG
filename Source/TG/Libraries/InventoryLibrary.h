// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TG/Enumerations.h"
#include "InventoryLibrary.generated.h"




USTRUCT(BlueprintType)
struct FInventoryGridRowsColumns
{
	GENERATED_BODY()
		FInventoryGridRowsColumns() 
	{
		columns = 0;
		rows = 0;
	}
	UPROPERTY(EditAnywhere)
		int32 columns;

	UPROPERTY(EditAnywhere)
		int32 rows;
};

/**
 * 
 */
UCLASS()
class TG_API UInventoryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION()
		static float GetInventorySlotSize(EInventoryType iInventoryType);

	UFUNCTION()
		static FInventoryGridRowsColumns GetInventoryGridRowsColumns(EInventoryType iInventoryType);

};
