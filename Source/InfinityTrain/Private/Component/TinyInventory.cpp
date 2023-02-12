// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TinyInventory.h"

UTinyInventory::UTinyInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTinyInventory::BeginPlay()
{
	Super::BeginPlay();
	
}


void UTinyInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTinyInventory::AddItems(TMap<UTinyItemAsset*, int32> LootItems)
{
}

void UTinyInventory::RemoveItem(FGuid ItemId)
{
}

