// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/BaseEnemyCharacter.h"
#include "Component/TinyInventory.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UTinyInventory>(TEXT("TinyInventoryComponent"));

}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	LocalPlayer = GetWorld()->GetFirstPlayerController();
	
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto LocalPlayerRotation = LocalPlayer->PlayerCameraManager->GetCameraRotation();

	SetActorRotation(
		FRotator(
		0.0f,
		LocalPlayerRotation.Yaw + 90.0f,
		LocalPlayerRotation.Pitch
	));
}

