// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Finders/ItemFinder.h"

FInventoryItemDefinition UInventoryComponent::EmptyItemDefinition = FInventoryItemDefinition();

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(false);

	// ...
}


UInventoryComponent* UInventoryComponent::GetInventoryComponentFromActor(AActor* actor)
{
	if (actor)
	{
		return actor->FindComponentByClass<UInventoryComponent>();
	}
	return nullptr;
}

void UInventoryComponent::AddItem(const FGameplayTag& itemTag, int itemStack)
{
	if (!DoItemExists(itemTag))
	{
		FInventoryItemDefinition newItemDefinition;
		newItemDefinition.ItemTypeTag = itemTag;
		newItemDefinition.Stack = itemStack;
		Items.Add(itemTag, newItemDefinition);
		OnInventoryItemAdded.Broadcast(newItemDefinition);
	}
	else
	{
		if (ItemFinder::IsItemStackable(itemTag))
		{
			FInventoryItemDefinition itemDefinition = GetEditableInventoryDefinitionFromItemTag(itemTag);
			itemDefinition.Stack += itemStack;
			OnInventoryItemAdded.Broadcast(itemDefinition);
		}
	}
}

void UInventoryComponent::UseItem(const FGameplayTag& itemTag, int itemStack)
{
	if (DoItemExists(itemTag))
	{
		FInventoryItemDefinition& editableItemInventoryDefinition = GetEditableInventoryDefinitionFromItemTag(itemTag);
		editableItemInventoryDefinition.Stack -= itemStack;
		OnInventoryItemUsed.Broadcast(editableItemInventoryDefinition, itemStack);
		if (editableItemInventoryDefinition.Stack <= 0)
		{
			RemoveItem(itemTag);
		}
	}
}

void UInventoryComponent::RemoveItem(const FGameplayTag& itemTag)
{
	Items.Remove(itemTag);
	OnInventoryItemRemoved.Broadcast();
}

const FInventoryItemDefinition& UInventoryComponent::GetInventoryDefinitionFromItemTag(const FGameplayTag& itemTag)
{
	return GetEditableInventoryDefinitionFromItemTag(itemTag);
}

FInventoryItemDefinition& UInventoryComponent::GetEditableInventoryDefinitionFromItemTag(const FGameplayTag& itemTag)
{
	if (Items.Contains(itemTag))
	{
		return Items[itemTag];
	}
	return EmptyItemDefinition;
}

TArray<FInventoryItemDefinition> UInventoryComponent::GetAllItems()
{
	TArray<FInventoryItemDefinition> valueArray;
	Items.GenerateValueArray(valueArray);
	return valueArray;
}

bool UInventoryComponent::DoItemExists(const FGameplayTag& itemTag)
{
	return GetInventoryDefinitionFromItemTag(itemTag).ItemTypeTag != EmptyItemDefinition.ItemTypeTag;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

