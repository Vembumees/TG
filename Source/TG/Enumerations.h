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
enum class EPlayerExploringStates : uint8
{
	EXPLORING					UMETA(DisplayName = "Exploring"),
	DIALOGUE					UMETA(DisplayName = "Idle")
};

UENUM(BlueprintType)
enum class ETGGameState : uint8
{
	MAINMENU					UMETA(DisplayName = "MAIN MENU"),
	MENUEXPLORE					UMETA(DisplayName = "EXPLORE MENU"),
	MENUDUEL					UMETA(DisplayName = "DUEL MENU"),
	DIALOGUEEXPLORE				UMETA(DisplayName = "EXPLORE DIALOGUE"),
	DIALOGUEDUEL				UMETA(DisplayName = "DUEL DIALOGUE"),
	INGAMEEXPLORE				UMETA(DisplayName = "INGAME EXPLORE"),
	INGAMEDUEL					UMETA(DisplayName = "INGAME DUEL"),
	DEATHSCREEN					UMETA(DisplayName = "DEATH SCREEN"),
};

UENUM(BlueprintType)
enum class EDialogueSelectButtons : uint8
{
	TALK					UMETA(DisplayName = "TALK"),
	ASK						UMETA(DisplayName = "ASK"),
	GIVE					UMETA(DisplayName = "GIVE"),
	TRADE					UMETA(DisplayName = "TRADE"),
	INVITE					UMETA(DisplayName = "INVITE TO GROUP"),
	DUEL					UMETA(DisplayName = "DUEL"),
	DUELPRACTICE			UMETA(DisplayName = "DUELPRACTICE"),
};

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	BAG						UMETA(DisplayName = "BAG"),
	CHEST					UMETA(DisplayName = "CHEST"),
	EQUIPMENT				UMETA(DisplayName = "EQUIPMENT"),
	SHOP					UMETA(DisplayName = "SHOP"),
};

UENUM(BlueprintType)
enum class EInventoryButtonBackgroundType : uint8
{
	NORMAL						UMETA(DisplayName = "NORMAL"),
	SELECTED					UMETA(DisplayName = "SELECTED"),
};

UENUM(BlueprintType)
enum class EMoveDirections : uint8
{
	UP						UMETA(DisplayName = "UP"),
	DOWN					UMETA(DisplayName = "DOWN"),
	LEFT						UMETA(DisplayName = "LEFT"),
	RIGHT					UMETA(DisplayName = "RIGHT"),
};