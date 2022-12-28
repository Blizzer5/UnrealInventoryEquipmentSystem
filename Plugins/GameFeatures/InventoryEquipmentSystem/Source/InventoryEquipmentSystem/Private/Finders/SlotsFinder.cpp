// Fill out your copyright notice in the Description page of Project Settings.


#include "Finders/SlotsFinder.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Defs/TableRowDefs.h"

TMap<FGameplayTag, const FInventorySlotDefinition*> SlotsFinder::InventorySlots = {};
TMap<FGameplayTag, const FEquipmentSlotDefinition*> SlotsFinder::EquipmentSlots = {};
SlotsFinder* SlotsFinder::SlotsFinderObject = nullptr;

void SlotsFinder::LoadAndSaveInventorySlotsDB(UDataTable* SlotsDT)
{
    if (!SlotsDT)
    {
        return;
    }
    InventorySlots.Empty();
    TArray<FInventorySlotDefinition*> DTSlots;
    SlotsDT->GetAllRows("", DTSlots);

    for (const FInventorySlotDefinition* slot : DTSlots)
    {
        InventorySlots.Add(slot->SlotTag, slot);
    }
}

void SlotsFinder::LoadAndSaveEquipmentSlotsDB(UDataTable* SlotsDT)
{
    if (!SlotsDT)
    {
        return;
    }
    EquipmentSlots.Empty();
    TArray<FEquipmentSlotDefinition*> DTSlots;
    SlotsDT->GetAllRows("", DTSlots);

    for (const FEquipmentSlotDefinition* slot : DTSlots)
    {
        EquipmentSlots.Add(slot->SlotTag, slot);
    }
}

int SlotsFinder::GetEquipmentSlotMaxHoldingNum(const FGameplayTag& SlotTag)
{
    if (EquipmentSlots.Contains(SlotTag))
    {
        return EquipmentSlots[SlotTag]->MaxHoldingItems;
    }
    return 0;
}

FName SlotsFinder::GetEquipmentSlotAttachmentSocket(const FGameplayTag& SlotTag)
{
    if (EquipmentSlots.Contains(SlotTag))
    {
        return EquipmentSlots[SlotTag]->SocketToAttachTo;
    }
    return FName();
}

SlotsFinder* SlotsFinder::GetSingleton()
{
    if (!SlotsFinderObject)
    {
        SlotsFinderObject = new SlotsFinder();
    }
    return SlotsFinderObject;
}
