// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TinyInventory.generated.h"

UENUM(BlueprintType)
enum ETinyItemType
{
	Weapon UMETA(DisplayName = "Weapon"),
	//Consumable UMETA(DisplayName = "Consumable"),
	//Armor UMETA(DisplayName = "Armor"),
	//Spell UMETA(DisplayName = "Spell")
};

UCLASS(Blueprintable)
class INFINITYTRAIN_API UTinyItemAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Id = FGuid();
	
	UPROPERTY(EditAnywhere, Category=ItemInfo)
	FText Name;

	UPROPERTY(EditAnywhere, Category=ItemInfo)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, Category=ItemInfo)
	bool CanStack;

	UPROPERTY(EditAnywhere, Category=ItemInfo)
	TEnumAsByte<ETinyItemType> ItemType;

	//object here
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INFINITYTRAIN_API UTinyInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTinyInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UTinyItemAsset*, int32> Items;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AddItems(TMap<UTinyItemAsset*, int32> LootItems);
	
	UFUNCTION()
	void RemoveItem(FGuid ItemId);
};
