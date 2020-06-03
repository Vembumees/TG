// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "TG/Components/InventoryComponent.h"
#include "TG/TGCharacter.h"
#include "TG/Item/Item.h"
#include "TG/StaticLibrary.h"
#include "TG/Projectiles/Projectile.h"
#include "TG/UI/ExplorerMode/InventorySlot.h"

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
	if (refTGCharacter->GetInventoryComponent()->refItemInventory[iIndex]->slotData.inventorySlotState == EInventorySlotState::EMPTY)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAbilityComponent::CastAbility on empty slot."));
		return;
	}

	AItem* l_selectedItem = refTGCharacter->GetInventoryComponent()->GetItemInventory()[iIndex]->slotData.refItem;
	
	if (l_selectedItem->currentItemData.bIsOnCooldown == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("item on cd."));
		return;
	}

	//gets the functionality depending on item type
	switch (l_selectedItem->currentItemData.itemType)
	{
	case EItemType::TOME:

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
			//getting random enum, idk yet if its good idea to hardcore all the abilities like this, but at least it 
			//works pretty simply

			
 			TArray<ECardListFire> tEnum = UStaticLibrary::EnumGetList<ECardListFire>("ECardListFire");
 			ECardListFire fireCards = tEnum[FMath::RandRange(0, 0)]; // !! atm changed it to cast only fireball for testing
			switch (fireCards)
			{
			case ECardListFire::FIREBALL:
				UE_LOG(LogTemp, Warning, TEXT("fireball"));
				{
					//projectile fireball sound and impact sound shoudl be inside the projectile class

					//should trigger character animation function inside the character class
					//this->refChar->playAnimation()   playanimation->setflipbookx if finished set back to old

					FVector loc;
					loc = refTGCharacter->GetActorLocation();
					if (refTGCharacter->bIsFacingRight)
					{
						loc.X += 20;
					}
					else
					{
						loc.X -= 20;
					}
					
				FActorSpawnParameters params;
				params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				params.Owner = this->GetOwner();
				AProjectile* fireBall = GetWorld()->SpawnActor<AProjectile>(defaultProjectile, loc,
					refTGCharacter->GetActorRotation(), params);
				
				}
				break;
			case ECardListFire::ENCHANTFIRE:
				UE_LOG(LogTemp, Warning, TEXT("enchantfire"));
				break;
			case ECardListFire::LIVINGBOMB:
				UE_LOG(LogTemp, Warning, TEXT("livingbomb"));
				break;
			case ECardListFire::FIREBLAST:
				UE_LOG(LogTemp, Warning, TEXT("fireblast"));
				break;
			case ECardListFire::FIRESHIELD:
				UE_LOG(LogTemp, Warning, TEXT("fireshield"));
				break;
			}
			
		

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
		break;
	case EItemType::SOUL:
		break;
	case EItemType::MYSTICAL:
		break;
	case EItemType::ARTIFACT:


		/* when we actually make it into making a game, equiping artifacts should only be able to be done at a gameplay altar or npc,
		but atm we make it a normal inventory interaction.
		
		equip item, so what it means is
		  add the item to first available artifact slot
		  if slots full, show message/log and do nothing.
		  
		  OR or BOTH

		  manually move the item to the artifact slot
		  select item
		  select slot to move it to 
		  and artifacts can only go to artifact slots or normal slots
		  if chosen slot already has an item switch places with it
		  
		  i need to implement the second part anyways so we can do it now? or later?*/


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

