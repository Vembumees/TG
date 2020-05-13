// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSelectionMenu.h"
#include "Components/HorizontalBox.h"
#include "DialogueSelectButton.h"
#include "TG/NPCs/MasterNPC.h"



void UDialogueSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeRefsInBP();
	InitializeReferences();

}

void UDialogueSelectionMenu::CreateDialogueButtons(const TArray<EDialogueSelectButtons>& iDialogueBtns)
{
	/*what do we want to implement?
	buttons that take their name and functionality from an enum.
	I want that in NPC data table I set an array of enums that 
	the buttons are created on. For example the array inside the
	character has ETalk, EDuel, ERecruit inside the NPC I call this
	function, pass these in here and create the buttons based on that.
	so I think variables I need to create are:
	2)EnumSelectDialogue
	3)Array<EnumSelectDialogue> (unique)
	4)
	so the function counts the number of entries in the array and builds the widgets based on that.
	*/
	
	/*reads the input and adds only unique values so we won't have 2 talks 
	when we make mistake in the datatable*/
	TArray<EDialogueSelectButtons> l_dialogueBtns;
	for (int i = 0; i <= iDialogueBtns.Num() - 1; i++)
	{		
		l_dialogueBtns.AddUnique(iDialogueBtns[i]);
	}
	

	if (!iDialogueBtns.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("UDialogueSelectionMenu::CreateDialogueButtons empty array input"));
		return;
	}

	//if this widget has been already called, clear previous children and create new ones
	if (bHaveTheButtonsAlreadyBeenCreated)
	{
		refDialogueMenuHorizontalBox->ClearChildren();
	}

	//Create buttons
	for (auto& e : l_dialogueBtns)
	{
		UE_LOG(LogTemp, Warning, TEXT("createBtn"));
		//dnt forget to add WBP correct to the Blueprint
		UDialogueSelectButton* wDialogueBtn = CreateWidget<UDialogueSelectButton>(GetWorld(), WBP_DialogueSelectButton);
		refDialogueMenuHorizontalBox->AddChildToHorizontalBox(wDialogueBtn);
		wDialogueBtn->refOwnerNPC = this->refOwnerNPC;
		wDialogueBtn->SetButtonText(e);
		wDialogueBtn->SetButtonBinding(e);
		bHaveTheButtonsAlreadyBeenCreated = true;
		
	}
	
	
	
}

void UDialogueSelectionMenu::InitializeReferences()
{
		
}