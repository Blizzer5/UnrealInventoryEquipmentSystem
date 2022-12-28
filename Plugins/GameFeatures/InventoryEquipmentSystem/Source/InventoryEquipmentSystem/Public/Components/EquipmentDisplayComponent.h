// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentDisplayComponent.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FDisplayedEquippedItem
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag itemTag;

	UPROPERTY()
	UStaticMeshComponent* displayedComponent;

	bool IsValid()
	{
		return itemTag.IsValid() && displayedComponent != nullptr;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYEQUIPMENTSYSTEM_API UEquipmentDisplayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentDisplayComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnItemEquipped(FGameplayTag equippedSlot, FGameplayTag equippedItem);
	UFUNCTION()
	void OnItemUnequipped(FGameplayTag unequippedSlot, FGameplayTag unequippedItem);
	
	UFUNCTION()
	void OnItemMeshLoaded(const FGameplayTag slotTag, const FGameplayTag itemTag, USkeletalMeshComponent* skeletalMesh, const FName socketToAttachTo);

private:
	TMap<FGameplayTag, TArray<FDisplayedEquippedItem>> AttachedItems;
	static FDisplayedEquippedItem EmptyDisplayedItem;

	FDisplayedEquippedItem& GetDisplayedItemFromSlotAndItemTag(const FGameplayTag& slotTag, const FGameplayTag& itemTag, int& indexOut);
};
