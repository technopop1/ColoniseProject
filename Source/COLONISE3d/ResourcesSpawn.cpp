// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcesSpawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TreeSpawn.h"

// Sets default values
AResourcesSpawn::AResourcesSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AResourcesSpawn::BeginPlay()
{
	Super::BeginPlay();
	const FActorSpawnParameters SpawnInfo;
	float WorldWidth = 25000.0f; // 20000
	for(int i = 0; i < 1000; i++)
	{
		if ( i%10 == 0)
		{
			FVector Location = FVector(FMath::RandRange(-WorldWidth, WorldWidth), FMath::RandRange(-WorldWidth, WorldWidth), 50.0f);
			FRotator Rotation = FRotator(0.0f, FMath::RandRange(-360.0f, 360.0f), 0.0f);
			ArrayOfRocks.Add(GetWorld()->SpawnActor<ARockSpawn>(ARockSpawn::StaticClass(), Location, Rotation, SpawnInfo));
		}
		else
		{
			FVector Location = FVector(FMath::RandRange(-WorldWidth, WorldWidth), FMath::RandRange(-WorldWidth, WorldWidth), 0.0f);
			FRotator Rotation = FRotator(0.0f, FMath::RandRange(-360.0f, 360.0f), 0.0f);
			ArrayOfTrees.Add(GetWorld()->SpawnActor<ATreeSpawn>(ATreeSpawn::StaticClass(), Location, Rotation, SpawnInfo));
		}
	}
}

// Called every frame
void AResourcesSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}