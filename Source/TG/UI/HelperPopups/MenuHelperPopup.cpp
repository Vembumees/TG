// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHelperPopup.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"


void UMenuHelperPopup::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
}

void UMenuHelperPopup::UpdateAllHelperData()
{
	UpdateHelperImage();
	UpdateHelperTextDescription();
	UpdateHelperTextTitle();
}

void UMenuHelperPopup::UpdateHelperImage()
{
// 	FSlateBrush brush;		
// 	brush.SetResourceObject(image);
// 	refHelperImage->SetBrush(brush);
}

void UMenuHelperPopup::UpdateHelperTextTitle()
{

}

void UMenuHelperPopup::UpdateHelperTextDescription()
{

}
