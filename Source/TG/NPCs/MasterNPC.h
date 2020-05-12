// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TG/Interfaces/Interact.h"
#include "MasterNPC.generated.h"

/**
 * 
 */

UCLASS()
class TG_API AMasterNPC : public APaperCharacter, public IInteract
{
	GENERATED_BODY()

		AMasterNPC();

protected:
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* dialogueAlert;
public:
	virtual void OnEnterPlayerRadius(AActor* iPlayer) override;

	virtual void OnLeavePlayerRadius(AActor* iPlayer) override;

	virtual void Interact(AActor* iPlayer) override;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


protected:

	void RotateTowardsPlayer();

	/* ###########################################################
					Animations
 ########################################################### */
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* idleAnimation;



protected:
	
};
