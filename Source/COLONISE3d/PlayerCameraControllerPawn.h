// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RockSpawn.h"
#include "TreeSpawn.h"
#include "UnitSpawn.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraControllerPawn.generated.h"

UCLASS()
class COLONISE3D_API APlayerCameraControllerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCameraControllerPawn();

	UPROPERTY(EditAnywhere);
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere);
	class APlayerController* PC;
	
	UPROPERTY(EditAnywhere);
	class UCameraComponent* Camera;

	TArray<AUnitSpawn*, TInlineAllocator<3>> Units;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	ATreeSpawn *Tree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	ARockSpawn *Rock = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	AMainWarehouseSpawn *WarehouseSpawn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FHitResult HitResults;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bCursorVisible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bMultiplySeletion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bLeftMouseClickPressed = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bWheelLock = false;		// change in blueprint - using to rotate while building

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void HorizontalRot(float Value);
	void ScrollZoomUp();
	void ScrollZoomDown();
	void CursorVisible();
	void UnselectUnits();
	void SetPropertiesForSelectedUnits(FHitResult Hit, bool bEmptyPlaceLocation);
	void LeftMouseClick();
	void RightMouseClick();
	void MultiplySelection(float Value);
	
};
