// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreController.h"
#include "TG/TGCharacter.h"
#include "TG/UI/TGHUD.h"

AExploreController::AExploreController()
{

}

void AExploreController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AExploreController::Jump);
	InputComponent->BindAction("BasicAttack", IE_Pressed, this, &AExploreController::BasicAttack);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AExploreController::Interact);
	InputComponent->BindAxis("MoveRight", this, &AExploreController::MoveRight);

	InputComponent->BindAction("ToggleIngameMenu", IE_Pressed, this, &AExploreController::ToggleIngameMenu);

}

void AExploreController::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle ExploreControllerInitRefsTimer;
	//this actors tick is set to 1 in bp
	GetWorld()->GetTimerManager().SetTimer(ExploreControllerInitRefsTimer, this, &AExploreController::InitializeRefs,
		0.5f, false);
	InitializeRefs();
}

void AExploreController::BasicAttack()
{
	if (refTGCharacter != nullptr)
	{
		refTGCharacter->BasicAttack();
	}
}

void AExploreController::Interact()
{
	if (refTGCharacter != nullptr)
	{
		refTGCharacter->Interact();
	}
}

void AExploreController::MoveRight(float iVal)
{
	if (refTGCharacter != nullptr)
	{
		refTGCharacter->MoveRight(iVal);
	}
}

void AExploreController::InitializeRefs()
{
	refTGCharacter = Cast<ATGCharacter>(this->GetPawn());

	/*HUD*/
	refHUD = Cast<ATGHUD>(this->GetHUD());
}

void AExploreController::Jump()
{
	if (refTGCharacter != nullptr)
	{
		refTGCharacter->Jump();
	}
}

void AExploreController::ToggleIngameMenu()
{
	if (refHUD != nullptr)
	{
		refHUD->ToggleIngameMenu();
	}
}
