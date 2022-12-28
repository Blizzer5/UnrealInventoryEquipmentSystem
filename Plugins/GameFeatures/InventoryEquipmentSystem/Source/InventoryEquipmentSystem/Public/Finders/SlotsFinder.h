// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FInventorySlotDefinition;
struct FEquipmentSlotDefinition;

/**
 * 
 */
class INVENTORYEQUIPMENTSYSTEM_API SlotsFinder
{
public:
	SlotsFinder() = default;
	SlotsFinder(SlotsFinder &other) = delete;
    void operator=(const SlotsFinder&) = delete;

	static void LoadAndSaveInventorySlotsDB(UDataTable* SlotsDT);
	static void LoadAndSaveEquipmentSlotsDB(UDataTable* SlotsDT);
	static int GetEquipmentSlotMaxHoldingNum(const FGameplayTag& SlotTag);
	static FName GetEquipmentSlotAttachmentSocket(const FGameplayTag& SlotTag);
private:
	static SlotsFinder* GetSingleton();
protected:
	static SlotsFinder* SlotsFinderObject;

	UPROPERTY()
	static TMap<FGameplayTag, const FInventorySlotDefinition*> InventorySlots;
    UPROPERTY()
    static TMap<FGameplayTag, const FEquipmentSlotDefinition*> EquipmentSlots;
};
