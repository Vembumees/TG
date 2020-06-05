// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "MenuHelperPopup.generated.h"

/**
 * This should be the class that has few images and text and shows what buttons do what. Like when player interacts with a new
   object for the first time. Should be able to be disabled in the menu.

   This beauty class
 */


USTRUCT(BlueprintType)
struct FHelperPopupData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		UTexture2D* helperImg;
	UPROPERTY(EditAnywhere)
		FText helperTitle;
	UPROPERTY(EditAnywhere)
		FText helperDescription;
};

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

	//TODO: !! I need to add "press X button to close this"

protected:
	virtual void NativeConstruct() override;

	//already doing the - 1 in the function
	void ReadData(int32 iDataRowNumber);

	UPROPERTY()
		TArray<FName> dtRowNames;

	
};
