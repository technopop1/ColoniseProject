// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Walls.generated.h"

UCLASS()
class COLONISE3D_API AWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	bool bIsAlive = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallLimit = 1000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString WallName = "Wall";
	
	
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
