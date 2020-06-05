// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class TG_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	/* #########################END############################## */
	
		/* ###########################################################
						References
	 ########################################################### */
	 /*passes the UMG variables from BP to here*/
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeBPReferences();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refMenuBtnBackground;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refMenuTitleText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UUniformGridPanel* refMenuUniformGridPanel;


	class AExploreController* refExploreController;

	/* #########################END############################## */
protected:
	virtual void NativeConstruct() override;




};
