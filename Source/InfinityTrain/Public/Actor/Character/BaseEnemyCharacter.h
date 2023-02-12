// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BaseEnemyCharacter.generated.h"

UCLASS()
class INFINITYTRAIN_API ABaseEnemyCharacter : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory, meta=(AllowPrivateAccess = "true"))
	class UTinyInventory* InventoryComponent;

public:
	ABaseEnemyCharacter();

protected:
	UPROPERTY()
	APlayerController* LocalPlayer;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
