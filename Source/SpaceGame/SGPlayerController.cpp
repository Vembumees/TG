// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"
#include "SpaceGame/Pawns/SGPlayerPawn.h"

ASGPlayerController::ASGPlayerController()
{


}



void ASGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ASGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASGPlayerController::MoveRight);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ASGPlayerController::Interact);
	InputComponent->BindAction("Attack", IE_Pressed, this, &ASGPlayerController::Attack);
}

void ASGPlayerController::MoveForward(float iVal)
{

	if (playerPawn != nullptr)
	{
		playerPawn->MoveForward(iVal);
	}
}

void ASGPlayerController::MoveRight(float iVal)
{
	if (playerPawn)
	{
		playerPawn->MoveRight(iVal);
	}
}

void ASGPlayerController::Interact()
{
	if (playerPawn)
	{
		playerPawn->Interact();
	}
}

void ASGPlayerController::Attack()
{
	if (playerPawn)
	{
		playerPawn->Attack();
	}
}

void ASGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	playerPawn = Cast<ASGPlayerPawn>(GetPawn());

}


