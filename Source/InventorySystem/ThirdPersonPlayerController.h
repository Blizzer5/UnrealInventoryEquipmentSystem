// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AThirdPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

};
