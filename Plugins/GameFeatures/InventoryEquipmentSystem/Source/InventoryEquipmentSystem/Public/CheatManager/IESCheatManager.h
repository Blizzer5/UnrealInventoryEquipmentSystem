// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "IESCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYEQUIPMENTSYSTEM_API UIESCheatManager : public UCheatManagerExtension
{
	GENERATED_BODY()
	
    UFUNCTION(exec)
    void SpawnItem(FName itemTag);

    UFUNCTION(exec)
    void EquipItem(FName slot, FName itemTag);
    UFUNCTION(exec)
    void UnequipItem(FName slot, FName itemTag);
};
