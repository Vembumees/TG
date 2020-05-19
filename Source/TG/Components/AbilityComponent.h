// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TG/Enumerations.h"
#include "AbilityComponent.generated.h"


/*Big spaghetti class where I do all the ability casting and logic*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TG_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();



	/* ###########################################################
					core - components, refs etc
	 ########################################################### */
public:
	 


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitializeRefs();


	/*references*/
	UPROPERTY()
		class ATGCharacter* refTGCharacter;


	 /* #########################END############################## */

	/* ###########################################################
							DATA
	########################################################### */
protected:


	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> defaultProjectile;









	/* #########################END############################## */

	/* ###########################################################
						Ability stuff
	 ########################################################### */
protected:


public:
	void CastAbility(int32 iIndex);







private:
	UFUNCTION()
		void TimerRemoveCooldown(class AItem* iRefItem);

	void StartCooldownTimer(class AItem* iRefItem);
	 /* #########################END############################## */


};
