#pragma once
#include "Engine/DataTable.h"
#include "Enumerations.h"
#include "DataTables.generated.h"

USTRUCT(BlueprintType)
struct FExample : public FTableRowBase
{
	GENERATED_BODY()

		//defaults
		FExample()
		{
			example = 3;
		}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 example;									//how many actionpoints ability costs

};