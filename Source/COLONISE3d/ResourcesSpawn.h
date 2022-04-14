// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RockSpawn.h"
#include "TreeSpawn.h"
#include "GameFramework/Actor.h"
#include "Containers/ContainerAllocationPolicies.h"
#include "ResourcesSpawn.generated.h"

class ABoxComponentSpawn;

UCLASS()
class COLONISE3D_API AResourcesSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourcesSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//TArray<ABoxComponentSpawn*, TInlineAllocator<20>> ArrayOfBoxes;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<ATreeSpawn*> ArrayOfTrees;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<ARockSpawn*> ArrayOfRocks;

};
