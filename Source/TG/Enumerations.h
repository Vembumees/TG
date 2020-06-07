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
enum class ESlotType : uint8
{
	NORMAL						UMETA(DisplayName = "NORMAL"),
	ARTIFACT					UMETA(DisplayName = "ARTIFACT"),
	SLOTTYPE2					UMETA(DisplayName = "SLOTTYPENONE"),
	SLOTTYPE3					UMETA(DisplayName = "SLOTTYPENONE"),
	SLOTTYPE4					UMETA(DisplayName = "SLOTTYPENONE"),
	SLOTTYPE5					UMETA(DisplayName = "SLOTTYPENONE"),
	SLOTTYPE6					UMETA(DisplayName = "SLOTTYPENONE"),
};



UENUM(BlueprintType)
enum class EMoveDirections : uint8
{
	UP						UMETA(DisplayName = "UP"),
	DOWN					UMETA(DisplayName = "DOWN"),
	LEFT						UMETA(DisplayName = "LEFT"),
	RIGHT					UMETA(DisplayName = "RIGHT"),
};



//OK THIS IS FIRST DECK THAT IM GONNA MAKE, 5 cards
UENUM(BlueprintType)
enum class ECardListFire : uint8
{
	FIREBALL = 0						UMETA(DisplayName = "Fireball"),	//shoot a fireball
	ENCHANTFIRE = 1					UMETA(DisplayName = "EnchantFire"), //fire damage deals more damage next x seconds
	LIVINGBOMB	= 2					UMETA(DisplayName = "Living Bomb"), //in 3 seconds explode self
	FIREBLAST	= 3					UMETA(DisplayName = "Fire Blast"),  //fire explosion in front of the player
	FIRESHIELD	= 4					UMETA(DisplayName = "Fire Shield"),  
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	NONE						UMETA(DisplayName = "NONE"),
	SUPPORT						UMETA(DisplayName = "Support"),
	OFFENSIVE						UMETA(DisplayName = "Offensive"),
	WORLD						UMETA(DisplayName = "World"),
};


//OK THIS IS FIRST DECK THAT IM GONNA MAKE, 5 cards
UENUM(BlueprintType)
enum class ECardMagicTypes : uint8
{
	NONE						UMETA(DisplayName = "NONE"),
	NATURE						UMETA(DisplayName = "NATURE"),
	FIRE						UMETA(DisplayName = "FIRE"),
	LIGHTNING						UMETA(DisplayName = "LIGHTNING"),
	ICE						UMETA(DisplayName = "ICE"),
	DARK						UMETA(DisplayName = "DARK"),
	CHAOS						UMETA(DisplayName = "CHAOS"),
	MIND						UMETA(DisplayName = "MIND"),
	EVIL						UMETA(DisplayName = "EVIL"),
	HATRED						UMETA(DisplayName = "HATRED"),
	BLOOD						UMETA(DisplayName = "BLOOD"),
	ANCIENT						UMETA(DisplayName = "ANCIENT"),
	DIMENSIONAL						UMETA(DisplayName = "DIMENSIONAL"),
	ELDRITCH						UMETA(DisplayName = "ELDRITCH"),
	CELESTIAL						UMETA(DisplayName = "CELESTIAL"),
	CURSED						UMETA(DisplayName = "CURSED"),
	DEMONIC						UMETA(DisplayName = "DEMONIC"),
	TIME						UMETA(DisplayName = "TIME"),
	BEAST						UMETA(DisplayName = "BEAST"),
	ILLUSION						UMETA(DisplayName = "ILLUSION"),
	ENCHANTMENT						UMETA(DisplayName = "ENCHANTMENT"),
	ETHER						UMETA(DisplayName = "ETHER"),
	SOUL						UMETA(DisplayName = "SOUL"),
	VIOLET						UMETA(DisplayName = "VIOLET"),
	ISTHAN						UMETA(DisplayName = "ISTHAN"),
	MYDIAN						UMETA(DisplayName = "MYDIAN"),
};

//negative conditions players can draw, causes -attributes mostly
UENUM(BlueprintType)
enum class ECardNegativeConditions : uint8
{
	NONE						UMETA(DisplayName = "NONE"),
	EXHAUSTION						UMETA(DisplayName = "Exhaustion"),	//basic attack
	DEPRESSION						UMETA(DisplayName = "Depression"),
	MINDCLOUD						UMETA(DisplayName = "Mind Cloud"),
	BACKPAIN						UMETA(DisplayName = "Back pain"),
	TOOTHPAIN						UMETA(DisplayName = "Tooth pain"),
};

UENUM(BlueprintType)
enum class ECardListPhysical : uint8
{
	ATTACK						UMETA(DisplayName = "Attack"),	//basic attack
};


UENUM(BlueprintType)
enum class EProjectileAbility : uint8
{
	NONE						UMETA(DisplayName = "NONE"),
	STRAIGHTPROJECTILE						UMETA(DisplayName = "Straight projectile"),
	BOUNCINGPROJECTILE						UMETA(DisplayName = "Bouncing projectile"),
	SHOTGUNPROJECTILE						UMETA(DisplayName = "Shotgun projectile"),
};

UENUM(BlueprintType)
enum class EInventorySlotState : uint8
{
	EMPTY						UMETA(DisplayName = "Empty"),
	HASITEM						UMETA(DisplayName = "Has Item"),
	HIDDEN						UMETA(DisplayName = "Is Hidden"),
	DISABLED						UMETA(DisplayName = "Is Disabled"),
};

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	MAINMENU						UMETA(DisplayName = "Main Menu"),
	OPTIONSMENU						UMETA(DisplayName = "Options Menu"),
	QUESTSELECT						UMETA(DisplayName = "Quest Select"),
};

//OK THIS IS FIRST DECK THAT IM GONNA MAKE, 5 cards
UENUM(BlueprintType)
enum class EMenuItemFunction : uint8
{
	NONE		,
	STARTGAME	,
	OPENSETTINGS,
	QUITGAME	,
	D			,
	E			,
	F			,
	G			,
	H			,
	I			,
	J			,
	K			,
	L			,
	M			,
};