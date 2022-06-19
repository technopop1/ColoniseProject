// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxComponentSpawn.h"
#include "UnitSpawn.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "RockSpawn.generated.h"

UCLASS()
class COLONISE3D_API ARockSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsAlive = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RockLimit = 3000;
	float SecondsOfGathering = 0.0;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Rock;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* RockTriggerVolume = nullptr;
	//ATriggerBox* RockTriggerVolume = nullptr;
	UBoxComponent* RockBox;
	
	//TArray<AUnitSpawn*, TInlineAllocator<3>> Units;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
