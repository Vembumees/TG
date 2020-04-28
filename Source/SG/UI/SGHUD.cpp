// Fill out your copyright notice in the Description page of Project Settings.


#include "SGHUD.h"
#include "MainUI.h"

void ASGHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainUIClass != nullptr)
	{
		refMainUI = CreateWidget<UMainUI>(GetWorld(), MainUIClass);
		if (refMainUI != nullptr)
		{
			refMainUI->AddToViewport();
		}
	}
	
}
