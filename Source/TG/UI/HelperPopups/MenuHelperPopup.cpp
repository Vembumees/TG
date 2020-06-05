// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHelperPopup.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Engine/DataTable.h"


void UMenuHelperPopup::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	ReadData(1);
}

void UMenuHelperPopup::ReadData(int32 iDataRowNumber)
{

	UDataTable* menuHelperDT = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/TG/BP/Data/DT_HelperPopupData.DT_HelperPopupData'")));
	if (menuHelperDT == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("menuHelperDT not found "));
	}
	dtRowNames = menuHelperDT->GetRowNames();
	FHelperPopupData* row = menuHelperDT->FindRow<FHelperPopupData>(dtRowNames[iDataRowNumber - 1], TEXT("LookupHelperData"));

	if (row != nullptr)
	{
		row->helperTitle;
		row->helperDescription;
		
		//helperimage
		FSlateBrush brush;
		brush.SetResourceObject(row->helperImg);
		refHelperImage->SetBrush(brush);


		//helperTextTitle
		refHelperTextTitle->SetText(row->helperTitle);

		//helper text description
		refHelperTextDescription->SetText(row->helperDescription);
	}
}