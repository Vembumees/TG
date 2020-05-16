// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryLibrary.h"

float UInventoryLibrary::GetInventorySlotSize(EInventoryType iInventoryType)
{
	float l_slotSize = 0;
	switch (iInventoryType)
	{
	case EInventoryType::BAG:
		l_slotSize = 60.0;
		break;
	case EInventoryType::CHEST:
		l_slotSize = 45.0;
		break;
	case EInventoryType::EQUIPMENT:
		l_slotSize = 50.0;
		break;
	case EInventoryType::SHOP:
		l_slotSize = 45.0;
		break;
	}
	return l_slotSize;
}

FInventoryGridRowsColumns UInventoryLibrary::GetInventoryGridRowsColumns(EInventoryType iInventoryType)
{
	FInventoryGridRowsColumns l_invSize;
	switch (iInventoryType)
	{
	case EInventoryType::BAG:
		l_invSize.rows = 3;
		l_invSize.columns = 3;
		break;
	case EInventoryType::CHEST:
		l_invSize.rows = 4;
		l_invSize.columns = 2;
		break;
	case EInventoryType::EQUIPMENT:
		l_invSize.rows = 3;
		l_invSize.columns = 3;
		break;
	case EInventoryType::SHOP:
		l_invSize.rows = 1;
		l_invSize.columns = 3;
		break;
	}

	return l_invSize;
}



