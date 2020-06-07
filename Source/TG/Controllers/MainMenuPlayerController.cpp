// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "TG/UI/MainMenuHUD.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	InitializeRefs();
}

void AMainMenuPlayerController::SetupInputComponent()
{	
	Super::SetupInputComponent();

	InputComponent->BindAction("MenuUP", IE_Pressed, this, &AMainMenuPlayerController::MenuUP);
	InputComponent->BindAction("MenuDOWN", IE_Pressed, this, &AMainMenuPlayerController::MenuDOWN);
	InputComponent->BindAction("MenuLEFT", IE_Pressed, this, &AMainMenuPlayerController::MenuLEFT);
	InputComponent->BindAction("MenuRIGHT", IE_Pressed, this, &AMainMenuPlayerController::MenuRIGHT);
	InputComponent->BindAction("MenuUSESELECTED", IE_Pressed, this, &AMainMenuPlayerController::MenuUSESELECTED);
	InputComponent->BindAction("DEBUGAddItem", IE_Pressed, this, &AMainMenuPlayerController::DebugAdditem);
}


void AMainMenuPlayerController::MenuUP()
{
	currMenuMoveDirection = EMoveDirections::UP;
	delegateMenuMove.Broadcast(currMenuMoveDirection);
}

void AMainMenuPlayerController::MenuDOWN()
{
	currMenuMoveDirection = EMoveDirections::DOWN;
	delegateMenuMove.Broadcast(currMenuMoveDirection);
}

void AMainMenuPlayerController::MenuLEFT()
{
	currMenuMoveDirection = EMoveDirections::LEFT;
	delegateMenuMove.Broadcast(currMenuMoveDirection);
}

void AMainMenuPlayerController::MenuRIGHT()
{
	currMenuMoveDirection = EMoveDirections::RIGHT;
	delegateMenuMove.Broadcast(currMenuMoveDirection);
}

void AMainMenuPlayerController::MenuUSESELECTED()
{
	delegateMenuUse.Broadcast();
}

void AMainMenuPlayerController::InitializeRefs()
{
		/*HUD*/
	refMainMenuHUD = Cast<AMainMenuHUD>(this->GetHUD());
}

void AMainMenuPlayerController::DebugAdditem()
{
	delegateDebugAddItem.Broadcast();
}
