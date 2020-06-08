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
	InputComponent->BindAction("MenuUSESELECTED", IE_Pressed, this, &AMainMenuPlayerController::MenuUSESELECTEDPRESSED);
	InputComponent->BindAction("MenuUSESELECTED", IE_Released, this, &AMainMenuPlayerController::MenuUSESELECTEDRELEASED);
	InputComponent->BindAction("DEBUGAction1", IE_Pressed, this, &AMainMenuPlayerController::DebugAction1);
	InputComponent->BindAction("DEBUGAction2", IE_Pressed, this, &AMainMenuPlayerController::DebugAction2);
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

void AMainMenuPlayerController::MenuUSESELECTEDPRESSED()
{
	delegateMenuUsePRESSED.Broadcast();
}

void AMainMenuPlayerController::MenuUSESELECTEDRELEASED()
{
	delegateMenuUseRELEASED.Broadcast();
}

void AMainMenuPlayerController::InitializeRefs()
{
		/*HUD*/
	refMainMenuHUD = Cast<AMainMenuHUD>(this->GetHUD());
}

void AMainMenuPlayerController::DebugAction1()
{
	delegateDebugAction1.Broadcast();
}

void AMainMenuPlayerController::DebugAction2()
{
	delegateDebugAction2.Broadcast();
}
