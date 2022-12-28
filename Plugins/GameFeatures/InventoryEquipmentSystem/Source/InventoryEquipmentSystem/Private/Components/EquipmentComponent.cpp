// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"
#include "Finders/SlotsFinder.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(false);
	// ...
}


void UEquipmentComponent::EquipItem(const FGameplayTag& equippedSlot, const FGameplayTag& equippedItemTag)
{
	if (CanSlotHoldItem(equippedSlot, equippedItemTag))
	{
		EquippedItems.FindOrAdd(equippedSlot).EquippedItems.Add(equippedItemTag);
		OnItemEquipped.Broadcast(equippedSlot, equippedItemTag);
	}
}

void UEquipmentComponent::UnequipItem(const FGameplayTag& unequipSlot, const FGameplayTag& unequipedItemTag)
{
	if (DoSlotHasItemTag(unequipSlot, unequipedItemTag))
	{
		EquippedItems[unequipSlot].EquippedItems.Remove(unequipedItemTag);
		OnItemUnequipped.Broadcast(unequipSlot, unequipedItemTag);
	}
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UEquipmentComponent::DoSlotHasItemTag(const FGameplayTag& slotTag, const FGameplayTag& itemTag)
{
	if (EquippedItems.Contains(slotTag))
	{
		return EquippedItems[slotTag].EquippedItems.Contains(itemTag);
	}
	return false;
}

bool UEquipmentComponent::CanSlotHoldItem(const FGameplayTag& slotTag, const FGameplayTag& itemTag)
{
	return !EquippedItems.Contains(slotTag) || EquippedItems[slotTag].EquippedItems.Num() < SlotsFinder::GetEquipmentSlotMaxHoldingNum(slotTag);
}

