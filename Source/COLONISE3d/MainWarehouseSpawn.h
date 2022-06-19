// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MainWarehouseSpawn.generated.h"

UCLASS()
class COLONISE3D_API AMainWarehouseSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainWarehouseSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float HealthLimit = 10000;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsAlive = true;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//float HealthLimit = 1000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString StructureName = "MainWarehouse";

};
