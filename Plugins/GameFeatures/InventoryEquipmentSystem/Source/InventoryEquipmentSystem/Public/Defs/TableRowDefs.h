#pragma once

#include "UObject/ObjectMacros.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "StructEnumDefs.h"
#include "TableRowDefs.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FItemDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta=(Categories="Item.ItemTypeTag"))
    FGameplayTag ItemTag;
    UPROPERTY(EditAnywhere, meta = (Categories = "Item.Type"))
    FGameplayTag ItemType;
    UPROPERTY(EditAnywhere)
    FText Name;
    UPROPERTY(EditAnywhere)
    FText SmallDescription;
    UPROPERTY(EditAnywhere)
    FText Description;
    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UTexture2D> ItemIcon;
    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UStaticMesh> StorableMesh;
    UPROPERTY(EditAnywhere, meta=(Categories="Item.Attribute"))
    FGameplayTagContainer Attributes;
    UPROPERTY(EditAnywhere)
    TArray<FEquipmentSlotAttachmentDefinition> AttachmentDefinitions; 
};

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FInventorySlotDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (Categories = "Slot.Inventory"))
    FGameplayTag SlotTag;
};

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FEquipmentSlotDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, meta = (Categories = "Slot.Equipment"))
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere)
    int MaxHoldingItems;

    UPROPERTY(EditAnywhere)
    FName SocketToAttachTo;
};