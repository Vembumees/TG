// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SGGameMode.h"
#include "SGPawn.h"

ASGGameMode::ASGGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ASGPawn::StaticClass();
}

