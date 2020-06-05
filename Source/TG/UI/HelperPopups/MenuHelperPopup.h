// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuHelperPopup.generated.h"

/**
 * This should be the class that has few images and text and shows what buttons do what. Like when player interacts with a new
   object for the first time. Should be able to be disabled in the menu.


   not gonna finish it now, atm I think i need to make a singleton that receives the data, so i can call it from here and get the 
   data inside the widget, since widgets dont have constructors i cant use constructorhelpers to get the Datatable.
 */
UCLASS()
class TG_API UMenuHelperPopup : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refHelperTextTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* refHelperTextDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UImage* refHelperImage; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* refHelperCloseButton;
protected:
	virtual void NativeConstruct() override;

	void UpdateAllHelperData();

	void UpdateHelperImage();
	void UpdateHelperTextTitle();
	void UpdateHelperTextDescription();

	
};
