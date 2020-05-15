// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TG/Enumerations.h"
#include "InventoryWidget.generated.h"


UCLASS()
class TG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeRefsInBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UUniformGridPanel* refInventoryGridPanel;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class UInventorySlot*> refInventorySlots;

	UPROPERTY(EditAnywhere)
	float invSize;

protected:
	virtual void NativeConstruct() override;


	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CreateInventorySlots();

	void AddDelegateBindings();
	
	UFUNCTION()
	void MoveInInventory(EMoveDirections iMoveDir);

	//dont forget to update the class in WBP with the BP one
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UInventorySlot> invSlotClass; 
};
