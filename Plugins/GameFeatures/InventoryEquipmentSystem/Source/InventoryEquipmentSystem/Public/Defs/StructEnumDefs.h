#pragma once

#include "UObject/ObjectMacros.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "StructEnumDefs.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FEquipmentSlotAttachmentDefinition
{
    GENERATED_BODY()

    // Slot defines the attachment slot
    UPROPERTY(EditAnywhere, meta = (Categories = "Slot.Equipment"))
    FGameplayTag EquipmentSlotTag;

    UPROPERTY(EditAnywhere)
    FVector AttachmentOffset;
};