// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceGameGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceGame/SGPlayerController.h"
#include "Pawns/SGPlayerPawn.h"

ASpaceGameGameMode::ASpaceGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP/Pawns/BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

