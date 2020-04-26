#pragma once
#include "Engine/DataTable.h"
#include "Enumerations.h"
#include "DataTables.generated.h"

USTRUCT(BlueprintType)
struct FObjectStats : public FTableRowBase
{
	GENERATED_BODY()

		//defaults
		FObjectStats()
		{
			health = 3;
		}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText interactMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> loot;

};