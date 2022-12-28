// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GameFeatureAction_LoadItemsDB.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Finders/ItemFinder.h"

void UGameFeatureAction_LoadItemsDB::OnGameFeatureActivating()
{
    if (bLoadDataTableAsync)
    {
        TArray<FSoftObjectPath> ItemsToStream;
        ItemsToStream.Add(ItemsDataTable.ToSoftObjectPath());
        UAssetManager::GetStreamableManager().RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &UGameFeatureAction_LoadItemsDB::OnDataTableAssetLoaded));
    }
    else
    {
        ItemsDataTable.ToSoftObjectPath().TryLoad();
        OnDataTableAssetLoaded();
    }
}

void UGameFeatureAction_LoadItemsDB::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
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
EDataValidationResult UGameFeatureAction_LoadItemsDB::IsDataValid(TArray<FText>& ValidationErrors)
{
    EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(ValidationErrors), EDataValidationResult::Valid);

    if (ItemsDataTable.IsNull())
    {
        Result = EDataValidationResult::Invalid;
        //ValidationErrors.Add(FText::Format(LOCTEXT("DataTableEntryIsNull", "Null Item Data Table")));
    }

    return Result;
}
#endif

void UGameFeatureAction_LoadItemsDB::OnDataTableAssetLoaded()
{
    ItemFinder::LoadAndSaveItemDB(Cast<UDataTable>(ItemsDataTable.ToSoftObjectPath().ResolveObject()));
    UAssetManager::GetStreamableManager().Unload(ItemsDataTable.ToSoftObjectPath());
}
