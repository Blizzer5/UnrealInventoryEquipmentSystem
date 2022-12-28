// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GameFeatureAction_LoadSlotsDB.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Finders/SlotsFinder.h"

void UGameFeatureAction_LoadSlotsDB::OnGameFeatureActivating()
{
    if (bLoadDataTableAsync)
    {
        TArray<FSoftObjectPath> ItemsToStream;
        ItemsToStream.Add(InventorySlotsDataTable.ToSoftObjectPath());
        ItemsToStream.Add(EquipmentSlotsDataTable.ToSoftObjectPath());
        UAssetManager::GetStreamableManager().RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &UGameFeatureAction_LoadSlotsDB::OnDataTableAssetsLoaded));
    }
    else
    {
        InventorySlotsDataTable.ToSoftObjectPath().TryLoad();
        EquipmentSlotsDataTable.ToSoftObjectPath().TryLoad();
        OnDataTableAssetsLoaded();
    }
}

void UGameFeatureAction_LoadSlotsDB::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
    //UCheatManager::UnregisterFromOnCheatManagerCreated(CheatManagerRegistrationHandle);
    //
    //for (TWeakObjectPtr<UCheatManagerExtension> ExtensionPtr : SpawnedCheatManagers)
    //{
    //    if (UCheatManagerExtension* Extension = ExtensionPtr.Get())
    //    {
    //        UCheatManager* CheatManager = CastChecked<UCheatManager>(Extension->GetOuter());
    //        CheatManager->RemoveCheatManagerExtension(Extension);
    //    }
    //}
    //SpawnedCheatManagers.Empty();
}

#if WITH_EDITOR
EDataValidationResult UGameFeatureAction_LoadSlotsDB::IsDataValid(TArray<FText>& ValidationErrors)
{
    EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(ValidationErrors), EDataValidationResult::Valid);

    if (InventorySlotsDataTable.IsNull() || EquipmentSlotsDataTable.IsNull())
    {
        Result = EDataValidationResult::Invalid;
        //ValidationErrors.Add(FText::Format(LOCTEXT("DataTableEntryIsNull", "Null Item Data Table")));
    }

    return Result;
}
#endif

void UGameFeatureAction_LoadSlotsDB::OnDataTableAssetsLoaded()
{
    SlotsFinder::LoadAndSaveInventorySlotsDB(Cast<UDataTable>(InventorySlotsDataTable.ToSoftObjectPath().ResolveObject()));
    SlotsFinder::LoadAndSaveEquipmentSlotsDB(Cast<UDataTable>(EquipmentSlotsDataTable.ToSoftObjectPath().ResolveObject()));
    UAssetManager::GetStreamableManager().Unload(InventorySlotsDataTable.ToSoftObjectPath());
    UAssetManager::GetStreamableManager().Unload(EquipmentSlotsDataTable.ToSoftObjectPath());
}
