// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SGHUD.generated.h"

/**
 * 
 */
UCLASS()
class SG_API ASGHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMainUI> MainUIClass;





	/*references*/
public:
	class UMainUI* refMainUI;


};
