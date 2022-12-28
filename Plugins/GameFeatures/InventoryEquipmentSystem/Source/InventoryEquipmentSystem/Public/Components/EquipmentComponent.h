// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EquipmentComponent.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FEquipmentSlotEquippedItems
{
	GENERATED_BODY()

	TArray<FGameplayTag> EquippedItems;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, FGameplayTag, slotTag, FGameplayTag, equippedItemTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnequipped, FGameplayTag, slotTag, FGameplayTag, unequippedItemTag);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYEQUIPMENTSYSTEM_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();
	UFUNCTION(BlueprintCallable)
	void EquipItem(const FGameplayTag& equippedSlot, const FGameplayTag& equippedItemTag);

	// We ask for the item tag because we might have slots that allow more than one item
	UFUNCTION(BlueprintCallable)
	void UnequipItem(const FGameplayTag& unequipSlot, const FGameplayTag& unequipedItemTag);

	FOnItemEquipped OnItemEquipped;
	FOnItemUnequipped OnItemUnequipped;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// SlotTag, SlotDefinition
	TMap<const FGameplayTag, FEquipmentSlotEquippedItems> EquippedItems;

private:
	bool DoSlotHasItemTag(const FGameplayTag& slotTag, const FGameplayTag& itemTag);
	bool CanSlotHoldItem(const FGameplayTag& slotTag, const FGameplayTag& itemTag);
		
};
