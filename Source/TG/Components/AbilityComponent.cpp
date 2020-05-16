// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "TG/Components/InventoryComponent.h"
#include "TG/TGCharacter.h"
#include "TG/Item/Item.h"
#include "TG/Projectiles/Projectile.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeRefs();
	
}

void UAbilityComponent::InitializeRefs()
{
	refTGCharacter = Cast<ATGCharacter>(this->GetOwner());
}

void UAbilityComponent::CastAbility(int32 iIndex)
{
	if (!refTGCharacter->GetInventoryComponent()->GetItemInventory().IsValidIndex(iIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UAbilityComponent::CastAbility invalid index."));
		return;
	}

	AItem* l_selectedItem = refTGCharacter->GetInventoryComponent()->GetItemInventory()[iIndex];
	
	if (l_selectedItem->currentItemData.bIsOnCooldown == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("item on cd."));
		return;
	}

	//gets the functionality depending on item type
	switch (l_selectedItem->currentItemData.itemType)
	{
	case EItemType::TOME:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype TOME"));

		//check what magic type the tome is
		switch (l_selectedItem->currentItemData.itemAbility.magicType)
		{
		case ECardMagicTypes::NONE:
			break;
		case ECardMagicTypes::NATURE:
			break;
		case ECardMagicTypes::FIRE:
			//in this demo we do fire magic tome

		{
			FActorSpawnParameters params;
			params.Owner = this->GetOwner();
			AProjectile* fireBall = GetWorld()->SpawnActor<AProjectile>(defaultProjectile, refTGCharacter->GetActorLocation(), 
				refTGCharacter->GetActorRotation(), params);
			fireBall->Start(refTGCharacter); //false is left, just some projectile code i quickly got randomly off github xD
			//quickly just make a projectile spawn 
		}

			break;
		case ECardMagicTypes::LIGHTNING:
			break;
		case ECardMagicTypes::ICE:
			break;
		case ECardMagicTypes::DARK:
			break;
		case ECardMagicTypes::CHAOS:
			break;
		case ECardMagicTypes::MIND:
			break;
		case ECardMagicTypes::EVIL:
			break;
		case ECardMagicTypes::HATRED:
			break;
		case ECardMagicTypes::BLOOD:
			break;
		case ECardMagicTypes::ANCIENT:
			break;
		case ECardMagicTypes::DIMENSIONAL:
			break;
		case ECardMagicTypes::ELDRITCH:
			break;
		case ECardMagicTypes::CELESTIAL:
			break;
		case ECardMagicTypes::CURSED:
			break;
		case ECardMagicTypes::DEMONIC:
			break;
		case ECardMagicTypes::TIME:
			break;
		case ECardMagicTypes::BEAST:
			break;
		case ECardMagicTypes::ILLUSION:
			break;
		case ECardMagicTypes::ENCHANTMENT:
			break;
		case ECardMagicTypes::ETHER:
			break;
		case ECardMagicTypes::SOUL:
			break;
		case ECardMagicTypes::VIOLET:
			break;
		case ECardMagicTypes::ISTHAN:
			break;
		case ECardMagicTypes::MYDIAN:
			break;
		default:
			break;
		}

		break;
	case EItemType::TOKEN:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype TOKEN"));
		break;
	case EItemType::SOUL:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype SOUL"));
		break;
	case EItemType::MYSTICAL:
		UE_LOG(LogTemp, Warning, TEXT("Using itemtype MYSTICAL"));
		break;
	}
	StartCooldownTimer(l_selectedItem);

	if (l_selectedItem->currentItemData.bIsConsumedOnUse)
	{
		//remove item from inventory and destroy it TODO !!
	}
}

void UAbilityComponent::TimerRemoveCooldown(class AItem* iRefItem)
{
	UE_LOG(LogTemp, Warning, TEXT("cdtimer end"));
	iRefItem->currentItemData.bIsOnCooldown = false;
}

void UAbilityComponent::StartCooldownTimer(class AItem* iRefItem)
{
	UE_LOG(LogTemp, Warning, TEXT("StartCDTImer"));
	FTimerHandle cdTimerHandle;
	FTimerDelegate cdTimerDelegate;
	cdTimerDelegate.BindUFunction(this, FName("TimerRemoveCooldown"), iRefItem);
	GetWorld()->GetTimerManager().SetTimer(cdTimerHandle, cdTimerDelegate, iRefItem->currentItemData.itemCooldown, false);
	iRefItem->currentItemData.bIsOnCooldown = true;
}

