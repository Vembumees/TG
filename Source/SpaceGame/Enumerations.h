#pragma once

#include "CoreMinimal.h"
#include "Enumerations.generated.h"


UENUM()
enum class EPattern : uint8
{
	None					UMETA(DisplayName = "None"),
	Linear					UMETA(DisplayName = "Linear"),
	Diagonal				UMETA(DisplayName = "Diagonal"),
	Diamond					UMETA(DisplayName = "Diamond"),
	Square					UMETA(DisplayName = "Square"),
};

UENUM(BlueprintType)
enum class EGroundTypes : uint8
{
	None					UMETA(DisplayName = "None"),
	Normal					UMETA(DisplayName = "Normal"),
	Difficult				UMETA(DisplayName = "Difficult"),
	ReallyDifficult			UMETA(DisplayName = "Really Difficult"),
	Impossible				UMETA(DisplayName = "Impossible"),
};