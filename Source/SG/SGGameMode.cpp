// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SGGameMode.h"
#include "Engine/DataTable.h"
#include "SGPawn.h"

ASGGameMode::ASGGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ASGPawn::StaticClass();

	/* ###########################################################
	DATA
########################################################### */
/*load object stats datatable automatically, datatable values are in beginplay*/
	static ConstructorHelpers::FObjectFinder<UDataTable> ObjectStatsDTObject(TEXT("DataTable'/Game/Data/ObjectDataDT.ObjectDataDT'"));
	if (ObjectStatsDTObject.Succeeded())
	{
		//Use CharacterStatsDataTable to access the table data
		DTObjectData = ObjectStatsDTObject.Object;
	}
}

void ASGGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetDTObjectDataRowNames();
	
}

void ASGGameMode::SetDTObjectDataRowNames()
{
	if (DTObjectData != nullptr)
	{
		DTObjectDataRowNames = DTObjectData->GetRowNames();
	}
}
