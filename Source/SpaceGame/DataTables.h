#pragma once
#include "Engine/DataTable.h"
#include "Enumerations.h"
#include "DataTables.generated.h"

USTRUCT(BlueprintType)
struct FAbilities : public FTableRowBase
{
	GENERATED_BODY()

		//defaults
		FAbilities()
		{
			cost = 3;
			damage = 1;
			range = { FVector2D(1.0, 0.0), FVector2D(0.0, 1.0), FVector2D(-1.0, 0.0), FVector2D(0.0, -1.0) };
			
			bIsHealing = false;
			cooldown = 1;
			criticalChance = 5;
			criticalDamage = 10;
			bCanAttackThroughwalls = false;
		}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 cost;									//how many actionpoints ability costs
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector2D> range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector2D> aoeRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsHealing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 criticalChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 criticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanAttackThroughwalls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPattern pattern;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 patternRangeMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 patternRangeMax;
};