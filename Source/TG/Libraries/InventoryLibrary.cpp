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

FInventoryGridData UInventoryLibrary::GetInventoryGridData(EInventoryType iInventoryType)
{
	//if i change these i also need to consider that getstartingslot doesnt divide properly with odd/even numbers and i need to change the
	//formula there depending on odd or even or change the logic.
	FInventoryGridData l_invSize;
	switch (iInventoryType)
	{
	case EInventoryType::BAG:
		l_invSize.rows = 3;
		l_invSize.columns = 7;

		//artifact/equipment indexes, if i actually want to make these slots modifyable this way i just have to replace magic numbers
		for (int i = 9; i <= 11; i++)
		{
			l_invSize.artifactIndexes.Add(i);
		}

		for (int i = 16; i <= 18; i++)
		{
			l_invSize.artifactIndexes.Add(i);
		}
		

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


float UInventoryLibrary::GetMenuInventorySlotSize(EMenuType iMenuType)
{
	int32 l_slotSize;
	switch (iMenuType)
	{
	case EMenuType::MAINMENU:
		l_slotSize = 100;
		break;
	case EMenuType::OPTIONSMENU:
		l_slotSize = 100;
		break;
	case EMenuType::QUESTSELECT:
		l_slotSize = 100;
		break;
	}
	return l_slotSize;
}

FMenuInventoryGridData UInventoryLibrary::GetMenuInventoryGridData(EMenuType iMenuType)
{
	FMenuInventoryGridData l_menuData;
	switch (iMenuType)
	{
	case EMenuType::MAINMENU:
		l_menuData.rows = 5;
		l_menuData.columns = 17;

		//set hidden indexes
		for (int i = 40; i < 45; i++)
		{
			l_menuData.hiddenIndexes.Add(i);
		}
		//set disabled indexes
		


		break;
	case EMenuType::OPTIONSMENU:
		
		break;
	case EMenuType::QUESTSELECT:
		
		break;
	}

	return l_menuData;
}

