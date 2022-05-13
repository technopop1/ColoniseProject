// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcesSpawn.h"

#include "Particles/ParticleSystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TreeSpawn.h"

#include "Kismet/KismetMathLibrary.h"

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
	int DistB = 500;
	int WH = 100;
	
	FRandomStream rgen = FRandomStream(FMath::Rand());
	float offsetX = rgen.FRandRange(-100'000,100'000);
	float offsetY = rgen.FRandRange(-100'000,100'000);
	TArray<FVector2D> RockPoses;
	for (int y = 0 ; y < 100 ; y += 2)
		for (int x = 0; x < 100; x += 2)
		{
			const float PosZ = FMath::PerlinNoise2D(FVector2D(x/10.0f+offsetX,y/10.0f+offsetY)); // 8 // 12

			if (PosZ > 0.0 )
			{
				FVector Location = FVector(	-WorldWidth+x*DistB+FMath::RandRange(-DistB, DistB),
											-WorldWidth+y*DistB+FMath::RandRange(-DistB, DistB), 0.0f);
				FRotator Rotation = FRotator(0.0f, FMath::RandRange(-360.0f, 360.0f), 0.0f);
				ArrayOfTrees.Add(GetWorld()->SpawnActor<ATreeSpawn>(ATreeSpawn::StaticClass(), Location, Rotation, SpawnInfo));
				ArrayOfTrees.Last()->SetActorScale3D(FVector(1.7f, 1.7f, 1.75f));
			}
			else
			{
				RockPoses.Add(FVector2D(-WorldWidth+x*DistB+FMath::RandRange(-DistB, DistB),
											-WorldWidth+y*DistB+FMath::RandRange(-DistB, DistB)));
			}
		}
	for(int i = 0; i < 99; i++)
	{
		
		//FVector Location = FVector(FMath::RandRange(-WorldWidth, WorldWidth), FMath::RandRange(-WorldWidth, WorldWidth), 50.0f);
		// spawn rocks on poses where trees not exist 
		int idx = FMath::RandRange(0,RockPoses.Num()-1);
		FVector Location = FVector(RockPoses[idx], 50.0f);
		RockPoses.RemoveAt(idx);
		FRotator Rotation = FRotator(0.0f, FMath::RandRange(-360.0f, 360.0f), 0.0f);
		ArrayOfRocks.Add(GetWorld()->SpawnActor<ARockSpawn>(ARockSpawn::StaticClass(), Location, Rotation, SpawnInfo));
		//ArrayOfRocks.Last()->SetActorScale3D(FVector(1.2f, 1.2f, 1.5f));
	}
}

// Called every frame
void AResourcesSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}