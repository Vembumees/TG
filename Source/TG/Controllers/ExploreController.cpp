// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreController.h"
#include "TG/TGCharacter.h"
#include "TG/UI/TGHUD.h"


//this whole block could be avoided with some refactoring/better code 
#include "TG/UI/Dialogue/DialogueSelectButton.h"
#include "TG/UI/Dialogue/DialogueSelectionMenu.h"
#include "Components/HorizontalBox.h"
#include "TG/NPCs/MasterNPC.h"

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

	InputComponent->BindAction("1", IE_Pressed, this, &AExploreController::SelectDialog1);
	InputComponent->BindAction("2", IE_Pressed, this, &AExploreController::SelectDialog2);
	InputComponent->BindAction("3", IE_Pressed, this, &AExploreController::SelectDialog3);
	InputComponent->BindAction("4", IE_Pressed, this, &AExploreController::SelectDialog4);

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
		refHUD->IngameMenuToggle();
	}
}

void AExploreController::SelectDialog1()
{
	UE_LOG(LogTemp, Warning, TEXT("AExploreController::SelectDialog1()"));
	SelectDialogByIndex(0);

}

void AExploreController::SelectDialog2()
{
	SelectDialogByIndex(1);
}

void AExploreController::SelectDialog3()
{
	SelectDialogByIndex(2);
}

void AExploreController::SelectDialog4()
{
	SelectDialogByIndex(3);
}

void AExploreController::SelectDialogByIndex(int32 iIdx)
{
	if (refTGCharacter->refCurrentlyInteractingNPC == nullptr ||
		refTGCharacter->refCurrentlyInteractingNPC->refDialogueSelectionMenu == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectDialogByIndex() 1st check fail"));
		return;
	}


	//finds a button and calls the function it it, checks if the npc has the dialogue button in the function
	UDialogueSelectButton* l_ref = Cast<UDialogueSelectButton>(refTGCharacter->refCurrentlyInteractingNPC->
		refDialogueSelectionMenu->refDialogueMenuHorizontalBox->GetChildAt(0));

	if (refTGCharacter->refCurrentlyInteractingNPC->refDialogueSelectionMenu->
		GetCurrentDialogueButtons().IsValidIndex(iIdx))
	{
		l_ref->CallButtonFunctionWithInput(refTGCharacter->refCurrentlyInteractingNPC->refDialogueSelectionMenu->
			GetCurrentDialogueButtons()[iIdx]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectDialogByIndex() 2nd check fail"));
	}
	
}
