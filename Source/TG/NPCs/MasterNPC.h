// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Interfaces/Interact.h"
#include "Engine/DataTable.h"
#include "MasterNPC.generated.h"

USTRUCT(BlueprintType)
struct FNPCDialogues: public FTableRowBase
{
	GENERATED_BODY()

		FNPCDialogues()
	{
		dialogueMessage = FText::FromString("Welcome to TG friend!");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText dialogueMessage;

};

UCLASS()
class TG_API AMasterNPC : public APaperCharacter, public IInteract
{
	GENERATED_BODY()

		AMasterNPC();

protected:
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* dialogueAlert;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* dialogueComp;	//dont forget to set the widget in the blueprint

public:
	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;

	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;

	virtual void Interact(AActor* iPlayer) override;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/* ###########################################################
						References
	 ########################################################### */
	class UDialogueWidget* refDialogueWidget;

	 /* #########################END############################## */

protected:

	void RotateTowardsPlayer(AActor* iPlayer);



	/* ###########################################################
					Animations
 ########################################################### */
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* idleAnimation;

	

	/* ###########################################################
						Dialogue
	 ########################################################### */
protected:
	UPROPERTY(EditAnywhere)
		TArray<FNPCDialogues> dialogueMessages;

	void ShowNextDialogueMessage();

	void InitDialogueMessageHack();
	int32 simpleDialogueCounter;
	 /* #########################END############################## */
};
