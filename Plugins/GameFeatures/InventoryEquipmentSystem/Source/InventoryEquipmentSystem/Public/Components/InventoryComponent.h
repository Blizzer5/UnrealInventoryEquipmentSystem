// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYEQUIPMENTSYSTEM_API FInventoryItemDefinition
{
	GENERATED_BODY()

	FGameplayTag ItemTypeTag;

	int Stack;

	bool IsValid()
	{
		return ItemTypeTag != FGameplayTag::EmptyTag;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAdded, FInventoryItemDefinition, itemAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemUsed, FInventoryItemDefinition, itemUsed, int, stackUsed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYEQUIPMENTSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	static UInventoryComponent* GetInventoryComponentFromActor(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void AddItem(const FGameplayTag& itemTag, int itemStack = 1);
	UFUNCTION(BlueprintCallable)
	void UseItem(const FGameplayTag& itemTag, int itemStack = 1);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(const FGameplayTag& itemTag);

	UFUNCTION(BlueprintCallable)
	const FInventoryItemDefinition& GetInventoryDefinitionFromItemTag(const FGameplayTag& itemTag);
	FInventoryItemDefinition& GetEditableInventoryDefinitionFromItemTag(const FGameplayTag& itemTag);

	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItemDefinition> GetAllItems();

	FOnInventoryItemAdded OnInventoryItemAdded;
	FOnInventoryItemRemoved OnInventoryItemRemoved;
	FOnInventoryItemUsed OnInventoryItemUsed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool DoItemExists(const FGameplayTag& itemTag);

	TMap<const FGameplayTag, FInventoryItemDefinition> Items;
	static FInventoryItemDefinition EmptyItemDefinition;
};
