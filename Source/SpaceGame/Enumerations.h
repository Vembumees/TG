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