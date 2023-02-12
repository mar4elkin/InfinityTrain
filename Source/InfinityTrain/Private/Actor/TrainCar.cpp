// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TrainCar.h"

#include "Actor/Character/BaseEnemyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrainCar::ATrainCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating subobjects
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	LeftWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWall"));
	RightWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWall"));
	//EnterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterBox"));
	ExitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitBox"));

	SetRootComponent(SceneComponent);
		
	//Attaching to root
	Ceiling->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Floor->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LeftWall->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RightWall->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//EnterBox->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExitBox->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	Ceiling->SetRelativeLocation(FVector3d(0.0f, 0.0f, 800.0f));
	Ceiling->SetRelativeScale3D(FVector3d(7.0f, 14.0f, 0.25f));
	
	Floor->SetRelativeScale3D(FVector3d(7.0f, 14.0f, 0.25f));

	LeftWall->SetRelativeLocation(FVector3d(672.0f, 0.0f, 0.0f));
	LeftWall->SetRelativeScale3D(FVector3d(0.25f, 14.0f, 8.0f));

	RightWall->SetRelativeScale3D(FVector3d(0.25f, 14.0f, 8.0f));

	//EnterBox->SetRelativeLocation(FVector3d(350.0f, 40.0f, 420.0f));
	//EnterBox->SetRelativeScale3D(FVector3d(10.035f, 1.0f, 11.7725f));

	ExitBox->SetRelativeLocation(FVector3d(350.0f, 1370.0f, 420.0f));
	ExitBox->SetRelativeScale3D(FVector3d(10.035f, 1.0f, 11.7725f));

	ExitBox->OnComponentBeginOverlap.AddDynamic(this, &ATrainCar::OnOverlapBegin);
}

void ATrainCar::BeginPlay()
{
	Super::BeginPlay();
	for (auto SpawnPoint: EnemySpawnPoints)
	{
		if (FMath::RandBool())
		{
			GetWorld()->SpawnActor<ABaseEnemyCharacter>(
				EnemyClass,
				SpawnPoint,
				FRotator()
			)->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

// Called every frame
void ATrainCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrainCar::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ExitBox->OnComponentBeginOverlap.RemoveDynamic(this, &ATrainCar::OnOverlapBegin);
	
	auto NextCarLocation = GetActorLocation();
	NextCarLocation.X = NextCarLocation.X + 1400.0f;
	
	GetWorld()->SpawnActor<ATrainCar>(
		GetClass(),
		NextCarLocation,
		GetActorRotation()
	);
	
	TArray<AActor*> OutActors;
	GetAttachedActors(OutActors);

	for (const auto AttachedActor: OutActors)
	{
		AttachedActor->Destroy();
	}
	Destroy();
}

