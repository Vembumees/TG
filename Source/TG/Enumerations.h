#pragma once

#include "CoreMinimal.h"
#include "Enumerations.generated.h"


//quick sketch
UENUM(BlueprintType)
enum class ECharacterStates : uint8
{
	DEAD					UMETA(DisplayName = "Dead"),
	IDLE					UMETA(DisplayName = "Idle"),
	WALKING					UMETA(DisplayName = "Walking"),
	RUNNING					UMETA(DisplayName = "Running"),
	ATTACKING				UMETA(DisplayName = "Attacking"),
	STUNNED					UMETA(DisplayName = "Stunned"),
	DAMAGED					UMETA(DisplayName = "Damaged"),
	FALLING					UMETA(DisplayName = "Falling"),
	JUMPING					UMETA(DisplayName = "Jumping"),
	SLIDING					UMETA(DisplayName = "Sliding"),
	CROUCHING				UMETA(DisplayName = "Crouching"),
};

UENUM(BlueprintType)
enum class ETGGameState : uint8
{
	MAINMENU					UMETA(DisplayName = "MAIN MENU"),
	MENUEXPLORE					UMETA(DisplayName = "EXPLORE MENU"),
	MENUDUEL					UMETA(DisplayName = "DUEL MENU"),
	DIALOGUEEXPLORE					UMETA(DisplayName = "EXPLORE DIALOGUE"),
	DIALOGUEDUEL					UMETA(DisplayName = "DUEL DIALOGUE"),
	INGAMEEXPLORE				UMETA(DisplayName = "INGAME EXPLORE"),
	INGAMEDUEL					UMETA(DisplayName = "INGAME DUEL"),
	DEATHSCREEN					UMETA(DisplayName = "DEATH SCREEN"),
};