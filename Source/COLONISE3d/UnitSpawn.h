// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "DestinationInterface.h"
#include "MainWarehouseSpawn.h"
#include "GameFramework/Character.h"
#include "UnitSpawn.generated.h"

UCLASS()
class COLONISE3D_API AUnitSpawn : public ACharacter, public IDestinationInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitSpawn();
	//void SetUnitAnimation(FString Path);

	void MoveUnit(float DeltaTime);//
	void SetPropertiesForSelectedUnit(FHitResult Hit, FVector NewPos);
	void SetPropertiesForSelectedUnit(FHitResult Hit, bool bEmptyPlaceLocation);
	void SetPropertiesForSelectedUnit(AActor* Object); // back from warehouse
	void ReachedLimit();
	void StopUnit();
	void AddResource();
	void CheckDestState();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bSelected = false;					// Unit selection state
	//bool bDestinationSelected = false;		// Unit destinationSelected state
	bool bUnitRotate = false;				// Unit rotation state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bUnitMove = false;					// Unit movement state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIfTree = false;					// Unit tree clicked state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIfRock = false;					// Unit rock clicked state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIfWarehouse = false;				// Unit warehouse clicked state
	UPROPERTY(VisibleAnywhere)
	bool bGathering = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Wood = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Food = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Stone = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Limit = 300;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AttackDmg = 10;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Health = 150;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GatheringSpeed = 10;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Status = "Ally";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SightDistance = 1000.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bFindRandomPatrol = false;
	
	
	UFUNCTION(BlueprintCallable)
	void CylinderHideShow();
	
	UFUNCTION(BlueprintCallable)
	void FindRandomPatrol();
	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed(float Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *UnitCylinder = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Destination;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterMovementComponent *UnitCharacterMovement = nullptr; 
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UBlackboardComponent * BB = nullptr;
	//UBehaviorTreeComponent* OwnerComp = nullptr;
	
public:		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* Warehouse;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* Unitcontroller;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ATreeSpawn* ClickedTree = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ARockSpawn* ClickedRock = nullptr;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//class AUnitSpawn* ClickedUnit = nullptr;

	USceneComponent* MyRoot; // RootComponent
	
};