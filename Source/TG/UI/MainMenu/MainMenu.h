// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"

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

	/* #########################END############################## */


	UPROPERTY(EditAnywhere)
		float menuInvSize;

	UPROPERTY(EditAnywhere)
		TMap<FVector2D, class UMainMenuSlot*> mapRefMenuSlots;

	UPROPERTY(EditAnywhere)
		TArray<class UMainMenuSlot*> mainMenuSlotsInventory;
	UPROPERTY(EditAnywhere)
		TArray<class UMainMenuSlot*> optionsMenuSlotsInventory;
	UPROPERTY(EditAnywhere)
		TArray<class UMainMenuSlot*> questSelectSlotsInventory;

	FVector2D currentlySelectedSlotCoord;
	FVector2D lastSelectedSlotCoord;

	UPROPERTY()
		class AMainMenuPlayerController* refMainMenuPlayerController;

	int32 GetCurrentlySelectedSlotIndex();
	void RefreshMenuSlots();

protected:

	void AddDelegateBindings();
	void InitializeRefs();

	virtual void NativeConstruct() override;

		
		void CreateMenuSlots();


	UFUNCTION()
		void UseSelectedSlot();
	
	void HighlightSelectedSlot();
	void DeHighlightSelectedSlot();
	void SelectNeightbourSlot(FVector2D iTarget);
	void GetStartingSlot();
	void GetRowIndexes(int32 iRow);


	/*unrelated to menu, but really what would be cool i think if you could*/
	int32 GetFirstEmptyInventorySlotIndex();
	UFUNCTION()
		void MoveInMenu(EMoveDirections iMoveDir);

	//dont forget to update the class in WBP with the BP one
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UMainMenuSlot> menuSlotClass;
	

	virtual void NativePreConstruct() override;

public:


};
