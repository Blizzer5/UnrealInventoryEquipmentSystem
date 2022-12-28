// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "StorableActor.generated.h"

UCLASS()
class INVENTORYEQUIPMENTSYSTEM_API AStorableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorableActor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	void SetStorableItem(const FGameplayTag& itemTag);
	void LoadItemMesh();
	void OnItemMeshLoaded();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	FGameplayTag representedItem;
};
