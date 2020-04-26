// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG/Interfaces/InteractInterface.h"
#include "SGObject.generated.h"

UCLASS()
class SG_API ASGObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGObject();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* objectMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Custom - Interact")
		void Interact(AActor* iInteractor);
	virtual void Interact_Implementation(AActor* iInteracter) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Custom - Interact")
		FText GetInteractMessage();	//prototype declaration
	virtual FText GetInteractMessage_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Custom - Interact")
		void IDamage(AActor* iAttacker);
	virtual void IDamage_Implementation(AActor* iAttacker) override;


	UPROPERTY()
	FText InteractMessage;
	
};
