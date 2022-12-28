// Fill out your copyright notice in the Description page of Project Settings.


#include "CheatManager/IESCheatManager.h"
#include "GameplayTagContainer.h"
#include "Actors/StorableActor.h"
#include "Components/EquipmentComponent.h"

void UIESCheatManager::SpawnItem(FName itemTag)
{
    FString out = "Item.ItemTypeTag.";
    itemTag.AppendString(out);
    FGameplayTag itemGameplayTag = FGameplayTag::RequestGameplayTag(FName(out));
    if (itemGameplayTag.IsValid())
    {
        APawn* firstPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();

        FTransform transform;
        transform.SetLocation(firstPlayer->GetActorLocation() + (firstPlayer->GetActorForwardVector() * 200));
        AStorableActor* storableActor = GetWorld()->SpawnActor<AStorableActor>(AStorableActor::StaticClass(), transform);
        storableActor->SetStorableItem(itemGameplayTag);
    }
}

void UIESCheatManager::EquipItem(FName slot, FName itemTag)
{
    FString out = "Item.ItemTypeTag.";
    itemTag.AppendString(out);
    FGameplayTag itemGameplayTag = FGameplayTag::RequestGameplayTag(FName(out));

    FString out2 = "Slot.Equipment.";
    slot.AppendString(out2);
    FGameplayTag slotGameplayTag = FGameplayTag::RequestGameplayTag(FName(out2));
    if (itemGameplayTag.IsValid() && slotGameplayTag.IsValid())
    {
        APawn* firstPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
        if (UEquipmentComponent* firstPlayerEquipmentComponent = firstPlayer->FindComponentByClass<UEquipmentComponent>())
        {
            firstPlayerEquipmentComponent->EquipItem(slotGameplayTag, itemGameplayTag);
        }
    }
}

void UIESCheatManager::UnequipItem(FName slot, FName itemTag)
{
    FString out = "Item.ItemTypeTag.";
    itemTag.AppendString(out);
    FGameplayTag itemGameplayTag = FGameplayTag::RequestGameplayTag(FName(out));

    FString out2 = "Slot.Equipment.";
    slot.AppendString(out2);
    FGameplayTag slotGameplayTag = FGameplayTag::RequestGameplayTag(FName(out2));
    if (itemGameplayTag.IsValid() && slotGameplayTag.IsValid())
    {
        APawn* firstPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
        if (UEquipmentComponent* firstPlayerEquipmentComponent = firstPlayer->FindComponentByClass<UEquipmentComponent>())
        {
            firstPlayerEquipmentComponent->UnequipItem(slotGameplayTag, itemGameplayTag);
        }
    }
}
