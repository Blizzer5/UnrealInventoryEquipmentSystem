// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentDisplayComponent.h"
#include "Components/EquipmentComponent.h"
#include "GameFramework/Character.h"
#include "Finders/SlotsFinder.h"
#include "Finders/ItemFinder.h"
#include "Engine/AssetManager.h"

FDisplayedEquippedItem UEquipmentDisplayComponent::EmptyDisplayedItem = FDisplayedEquippedItem();

// Sets default values for this component's properties
UEquipmentDisplayComponent::UEquipmentDisplayComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UEquipmentDisplayComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEquipmentComponent* EquipmentComponent = GetOwner()->FindComponentByClass<UEquipmentComponent>())
	{
		EquipmentComponent->OnItemEquipped.AddDynamic(this, &UEquipmentDisplayComponent::OnItemEquipped);
		EquipmentComponent->OnItemUnequipped.AddDynamic(this, &UEquipmentDisplayComponent::OnItemUnequipped);
	}	
}

void UEquipmentDisplayComponent::OnItemEquipped(FGameplayTag equippedSlot, FGameplayTag equippedItem)
{
	if (USkeletalMeshComponent* ownerMesh = Cast<ACharacter>(GetOwner())->GetMesh())
	{
		FName socketToAttachTo = SlotsFinder::GetEquipmentSlotAttachmentSocket(equippedSlot);
		if (!socketToAttachTo.IsNone())
		{
            TArray<FSoftObjectPath> ItemsToStream;
            ItemsToStream.Add(ItemFinder::GetItemMeshSoftObjectPath(equippedItem).GetValue());
            UAssetManager::GetStreamableManager().RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &UEquipmentDisplayComponent::OnItemMeshLoaded,equippedSlot, equippedItem, ownerMesh, socketToAttachTo));
		}
	}
}

void UEquipmentDisplayComponent::OnItemUnequipped(FGameplayTag unequippedSlot, FGameplayTag unequippedItem)
{
	int index = 0;
	FDisplayedEquippedItem& displayedItem = GetDisplayedItemFromSlotAndItemTag(unequippedSlot, unequippedItem, index);
	if (displayedItem.IsValid())
	{
		AttachedItems[unequippedSlot].RemoveAt(index);
		displayedItem.displayedComponent->DetachFromParent();
		displayedItem.displayedComponent->UnregisterComponent();
	}
}

void UEquipmentDisplayComponent::OnItemMeshLoaded(const FGameplayTag slotTag, const FGameplayTag itemTag, USkeletalMeshComponent* skeletalMesh, const FName socketToAttachTo)
{
	if (UStaticMesh* itemMesh = Cast<UStaticMesh>(ItemFinder::GetItemMeshSoftObjectPath(itemTag).GetValue().ResolveObject()))
	{
		UStaticMeshComponent* newStaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner(), TEXT("ItemMeshComponent"));
		newStaticMeshComponent->SetStaticMesh(itemMesh);
		newStaticMeshComponent->AttachToComponent(skeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, socketToAttachTo);
		newStaticMeshComponent->SetRelativeLocation(FVector::ZeroVector);
		newStaticMeshComponent->RegisterComponent();

		FDisplayedEquippedItem newDisplayedItem;
		newDisplayedItem.itemTag = itemTag;
		newDisplayedItem.displayedComponent = newStaticMeshComponent;
		AttachedItems.FindOrAdd(slotTag).Add(newDisplayedItem);
	}
}

FDisplayedEquippedItem& UEquipmentDisplayComponent::GetDisplayedItemFromSlotAndItemTag(const FGameplayTag& slotTag, const FGameplayTag& itemTag, int& indexOut)
{
	indexOut = 0;
	if (AttachedItems.Contains(slotTag))
	{
		for (FDisplayedEquippedItem& displayedItem : AttachedItems[slotTag])
		{
			if (displayedItem.itemTag == itemTag)
			{
				return displayedItem;
			}
			indexOut++;
		}
	}
	return EmptyDisplayedItem;
}

