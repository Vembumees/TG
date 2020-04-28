// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "SG/Interfaces/InteractInterface.h"
#include "SGObject.generated.h"

USTRUCT(BlueprintType)
struct FObjectStats : public FTableRowBase
{
	GENERATED_BODY()

		FObjectStats()
		{
			objName = FText::FromString("Object");
			health = 1;
			interactMessage = FText::FromString("This is an object!");
		}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText objName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* staticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterialInstance* material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText interactMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> loot;
};

USTRUCT(BlueprintType)
struct FObjectData : public FTableRowBase
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FObjectStats objStats;
};

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


protected:

	void InitializeComponentsFromData();

	/*Enter the row you want the object to use*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom - Player Data")
		int32 DTObjectStatsRowNumber;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom - Player Data")
		FObjectStats ObjectsCurrentStats;
	

	/* ###########################################################
						References
	 ########################################################### */
protected:
	void InitNecessaryRefs();
	class ASGGameMode* refGameMode;
};
