// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxComponentSpawn.h"
#include "UnitSpawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TreeSpawn.generated.h"

UCLASS()
class COLONISE3D_API ATreeSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool bIsAlive = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TreeLimit = 1500;
	float SecondsOfGathering = 0.0;
	float TreeScaleValue = 1.0;
	
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Tree;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* TreeBox;
	
	// class AUnitSpawn* Units;
	TArray<AUnitSpawn*, TInlineAllocator<3>> Units;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
