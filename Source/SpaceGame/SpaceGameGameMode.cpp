// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceGameGameMode.h"
#include "SpaceGamePawn.h"

ASpaceGameGameMode::ASpaceGameGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ASpaceGamePawn::StaticClass();
}

