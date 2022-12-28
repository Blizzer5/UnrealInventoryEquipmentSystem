// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StorableActor.h"
#include "Finders/ItemFinder.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Components/InventoryComponent.h"

// Sets default values
AStorableActor::AStorableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionProfileName("OverlapAllDynamic");
}

void AStorableActor::SetStorableItem(const FGameplayTag& itemTag)
{
	if (itemTag.IsValid())
	{
		representedItem = itemTag;
		LoadItemMesh();
	}
}

void AStorableActor::LoadItemMesh()
{
    TArray<FSoftObjectPath> ItemToStream;
    ItemToStream.Add(ItemFinder::GetItemMeshSoftObjectPath(representedItem).GetValue());
    UAssetManager::GetStreamableManager().RequestAsyncLoad(ItemToStream, FStreamableDelegate::CreateUObject(this, &AStorableActor::OnItemMeshLoaded));
}

void AStorableActor::OnItemMeshLoaded()
{
	if (UStaticMesh* itemStorableMesh = Cast<UStaticMesh>(ItemFinder::GetItemMeshSoftObjectPath(representedItem).GetValue().ResolveObject()))
	{
		StaticMesh->SetStaticMesh(itemStorableMesh);
	}
}

// Called when the game starts or when spawned
void AStorableActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Without interaction system, the only way to pick up is when we overlap
	if (StaticMesh)
	{
		StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AStorableActor::OnActorOverlapped);
	}
}

void AStorableActor::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UInventoryComponent* InventoryComponent = UInventoryComponent::GetInventoryComponentFromActor(OtherActor))
	{
		InventoryComponent->AddItem(representedItem);
		UAssetManager::GetStreamableManager().Unload(ItemFinder::GetItemMeshSoftObjectPath(representedItem).GetValue());
		Destroy();
	}
}

