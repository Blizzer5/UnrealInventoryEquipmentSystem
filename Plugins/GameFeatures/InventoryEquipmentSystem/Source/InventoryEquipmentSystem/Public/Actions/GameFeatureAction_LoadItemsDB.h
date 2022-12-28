// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GameFeatureAction_LoadItemsDB.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Load Items DB"))
class INVENTORYEQUIPMENTSYSTEM_API UGameFeatureAction_LoadItemsDB : public UGameFeatureAction
{
	GENERATED_BODY()
	
    //~UGameFeatureAction interface
    virtual void OnGameFeatureActivating() override;
    virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
    //~End of UGameFeatureAction interface

    //~UObject interface
#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
    //~End of UObject interface

public:
    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<class UDataTable> ItemsDataTable;

    UPROPERTY(EditAnywhere)
    bool bLoadDataTableAsync;

private:
    UFUNCTION()
    void OnDataTableAssetLoaded();
};
