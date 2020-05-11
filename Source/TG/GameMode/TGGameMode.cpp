// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TGGameMode.h"
#include "TG/TGCharacter.h"

ATGGameMode::ATGGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ATGCharacter::StaticClass();	
}
