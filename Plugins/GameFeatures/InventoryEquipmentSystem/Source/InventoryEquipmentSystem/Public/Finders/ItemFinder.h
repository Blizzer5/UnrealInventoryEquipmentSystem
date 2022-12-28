// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FItemDefinition;

/**
 * 
 */
class INVENTORYEQUIPMENTSYSTEM_API ItemFinder
{
public:
	ItemFinder() = default;
	ItemFinder(ItemFinder &other) = delete;
    void operator=(const ItemFinder&) = delete;

	static void LoadAndSaveItemDB(UDataTable* DTToLoad);
	static bool IsItemStackable(const FGameplayTag& itemTag);
	static TOptional<FSoftObjectPath> GetItemMeshSoftObjectPath(const FGameplayTag& itemTag);
private:
	static ItemFinder* GetSingleton();
protected:
	static ItemFinder* ItemFinderObject;

	UPROPERTY()
	static TMap<FGameplayTag, const FItemDefinition*> Items;
};
