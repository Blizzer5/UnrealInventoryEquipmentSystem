// Fill out your copyright notice in the Description page of Project Settings.


#include "Finders/ItemFinder.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Defs/TableRowDefs.h"

TMap<FGameplayTag, const FItemDefinition*> ItemFinder::Items = {};
ItemFinder* ItemFinder::ItemFinderObject = nullptr;

void ItemFinder::LoadAndSaveItemDB(UDataTable* DTToLoad)
{
    if (!DTToLoad)
    {
        return;
    }
    Items.Empty();
    TArray<FItemDefinition*> DTItems;
    DTToLoad->GetAllRows("", DTItems);

    for (const FItemDefinition* item : DTItems)
    {
        Items.Add(item->ItemTag, item);
    }
}

bool ItemFinder::IsItemStackable(const FGameplayTag& itemTag)
{
    if(Items.Contains(itemTag))
    {
        return Items[itemTag]->Attributes.HasTagExact(FGameplayTag::RequestGameplayTag("Item.Attribute.IsStackable"));
    }
    return false;
}

TOptional<FSoftObjectPath> ItemFinder::GetItemMeshSoftObjectPath(const FGameplayTag& itemTag)
{
    if (Items.Contains(itemTag))
    {
        return Items[itemTag]->StorableMesh.ToSoftObjectPath();
    }
    return {};
}

ItemFinder* ItemFinder::GetSingleton()
{
    if (!ItemFinderObject)
    {
        ItemFinderObject = new ItemFinder();
    }
    return ItemFinderObject;
}
