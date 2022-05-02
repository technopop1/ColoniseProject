// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCameraControllerPawn.h"

#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/EngineTypes.h"
#include "UnitSpawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCameraControllerPawn::APlayerCameraControllerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Kamera porusza się względem mesha
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Mesh);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// set pos and rot of cam
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 2500.0f));
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void APlayerCameraControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = GetWorld()->GetFirstPlayerController();
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
}
// Called every frame
void APlayerCameraControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCameraControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCameraControllerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCameraControllerPawn::MoveRight);
	PlayerInputComponent->BindAxis("HorizontalRot", this, &APlayerCameraControllerPawn::HorizontalRot);
	PlayerInputComponent->BindAxis("MultiplySelection", this, &APlayerCameraControllerPawn::MultiplySelection);
	PlayerInputComponent->BindAction("CursorVisible", IE_Pressed, this, &APlayerCameraControllerPawn::CursorVisible);
	PlayerInputComponent->BindAction("ScrollZoomUp", IE_Pressed, this, &APlayerCameraControllerPawn::ScrollZoomUp);
	PlayerInputComponent->BindAction("ScrollZoomDown", IE_Pressed, this, &APlayerCameraControllerPawn::ScrollZoomDown);
	PlayerInputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &APlayerCameraControllerPawn::LeftMouseClick);
	PlayerInputComponent->BindAction("RightMouseClick", IE_Pressed, this, &APlayerCameraControllerPawn::RightMouseClick);
	//PlayerInputComponent->BindAction("CtrlLeftMouseClick", IE_Pressed, this, &APlayerCameraControllerPawn::CtrlLeftMouseClick);
}

void  APlayerCameraControllerPawn::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector()*5, Value);

}
void  APlayerCameraControllerPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()*5, Value);

}
void  APlayerCameraControllerPawn::HorizontalRot(float Value)
{
	AddActorLocalRotation(FRotator(0, Value, 0));
}
void  APlayerCameraControllerPawn::ScrollZoomUp()
{
	if (!bWheelLock)
	{
		Camera->FieldOfView -= 5 ;
		Camera->FieldOfView = FMath::Clamp(Camera->FieldOfView, 25.0f, 100.0f);
	}
}
void  APlayerCameraControllerPawn::ScrollZoomDown()
{
	if (!bWheelLock)
	{
		Camera->FieldOfView += 5;
		Camera->FieldOfView = FMath::Clamp(Camera->FieldOfView, 25.0f, 100.0f);
	}
}

void APlayerCameraControllerPawn::CursorVisible()
{
	if (!PC->bShowMouseCursor)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		bCursorVisible = false;
	}
	else if (PC->bShowMouseCursor)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
		bCursorVisible = true;
	}
}

void APlayerCameraControllerPawn::UnselectUnits()
{
	for (int i = 0; i < Units.Num(); ++i)
	{
		if (Units[i] != nullptr) 
			Units[i]->bSelected = false;
	}
	Units.Empty();
}

void APlayerCameraControllerPawn::SetPropertiesForSelectedUnits(FHitResult Hit, bool bEmptyPlaceLocation)
{
	float Distance = 200.0f;
	float NewX = 0.0f;
	float NewY = 0.0f;
	int Cols = 0;								//	define num of cols and row
	Cols = ceil(sqrt(Units.Num()));		
	
	for (int i = 0; i < Units.Num(); ++i)
	{
		if (Units[i] != nullptr &&  Hit.GetActor() != nullptr && bEmptyPlaceLocation)	// if empty place destination
		{
			if ( Cols%2 ) {
				NewX = -((Cols/2)*Distance) + (i-(i/Cols)*Cols)*Distance - Distance/2;
			}
			else {
				NewX = -(static_cast<float>(Cols/2)*Distance) + (i-(i/Cols)*Cols)*Distance;
			}
			NewY = (i/Cols)*Distance;
			Units[i]->SetPropertiesForSelectedUnit(Hit, bEmptyPlaceLocation, FVector(NewX, NewY, 0.0));
			//Units[i]->GetCapsuleComponent()->Setrespon*/
		}
		else if (Units[i] != nullptr)
		{
			Units[i]->SetPropertiesForSelectedUnit(Hit, bEmptyPlaceLocation);
		}
	}
	Units.Empty();
}


void APlayerCameraControllerPawn::LeftMouseClick()
{
	if (bLeftMouseClickPressed) bLeftMouseClickPressed = false;	// using for wall spawn...
	else bLeftMouseClickPressed = true;
	
	if(!bCursorVisible) // if cursor is visible then you can select by RMB 
	{
		APlayerController* Mouse = Cast<APlayerController>(GetController());

		FVector StartM;
		FVector DirectionM;
		Mouse->DeprojectMousePositionToWorld(StartM, DirectionM);

		FHitResult Hit; // (ForceInit)
		HitResults = Hit;
		
		FVector End(StartM + ( DirectionM * 10000));
		//FCollisionQueryParams TraceParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartM, End, ECC_Visibility, FCollisionQueryParams());
	
		if (Hit.GetActor() != nullptr && bHit)
		{
			///// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("Trace Hit: %s"), *Hit.GetActor()->GetName()));
			if( Cast<AUnitSpawn>(Hit.GetActor()) )
			{
				Cast<AUnitSpawn>(Hit.GetActor())->bSelected = true;
				Units.Add(Cast<AUnitSpawn>(Hit.GetActor()));
				Rock = nullptr;
				Tree = nullptr;
				WarehouseSpawn = nullptr;
				Wall = nullptr;
			}
			else if( Cast<ATreeSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )				// If gatherable object was clicked... and // just save tapped tree
			{
				Tree = Cast<ATreeSpawn>(Hit.GetActor());
				Rock = nullptr;
				WarehouseSpawn = nullptr;
				Wall = nullptr;
				UnselectUnits();
			}
			else if( Cast<ARockSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{
				Rock = Cast<ARockSpawn>(Hit.GetActor());
				Tree = nullptr;
				WarehouseSpawn = nullptr;
				Wall = nullptr;
				UnselectUnits();
			}
			else if( Cast<AMainWarehouseSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{ 
				WarehouseSpawn = Cast<AMainWarehouseSpawn>(Hit.GetActor());
				Tree = nullptr;
				Rock = nullptr;
				Wall = nullptr;
				UnselectUnits();
			}
			else if( Cast<AWalls>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{ 
				Wall = Cast<AWalls>(Hit.GetActor());
				WarehouseSpawn = nullptr;
				Tree = nullptr;
				Rock = nullptr;
				UnselectUnits();
			}
			else if (Hit.GetActor() != nullptr )	// clear select state on lmb 
				{
				Rock = nullptr;
				Tree = nullptr;
				WarehouseSpawn = nullptr;
				UnselectUnits();
				}
		}
	}
}

void APlayerCameraControllerPawn::RightMouseClick()
{

	if(!bCursorVisible) // if cursor is visible then you can select by RMB 
	{
		APlayerController* Mouse = Cast<APlayerController>(GetController());

		FVector StartM;
		FVector DirectionM;
		Mouse->DeprojectMousePositionToWorld(StartM, DirectionM);

		FHitResult Hit; // (ForceInit)
	
		FVector End(StartM + ( DirectionM * 10000));								
		//TArray<FHitResult> Hit_for_line; // niepotrzebne potem
		FCollisionQueryParams TraceParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartM, End, ECC_Visibility, TraceParams);
		///// DrawDebugLine(GetWorld(), StartM, End, FColor::Orange, false, 0.1f);
		///// DrawLineTraces(GetWorld(), StartM, End, Hit_for_line, 1.0f);
	
		if (Hit.GetActor() != nullptr && bHit)
		{
			////// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("Trace Hit: %s"), *Hit.GetActor()->GetName()));
			if( Cast<ATreeSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )		// If gatherable object was clicked... and // IF gatherer was selected before ...
			{
				for (int i = 0; i < Units.Num(); ++i)
				{
					if (Units[i] != nullptr)
					{
						Units[i]->ClickedTree = Cast<ATreeSpawn>(Hit.GetActor());
						Units[i]->ClickedRock = nullptr;
					}
				}
				SetPropertiesForSelectedUnits(Hit, false);
			}
			else if( Cast<ARockSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{
				for (int i = 0; i < Units.Num(); ++i)
				{
					if (Units[i] != nullptr)
					{
						Units[i]->ClickedRock = Cast<ARockSpawn>(Hit.GetActor());
						Units[i]->ClickedTree = nullptr;
					}
				}
				SetPropertiesForSelectedUnits(Hit, false);
			}
			else if( Cast<AMainWarehouseSpawn>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{
				for (int i = 0; i < Units.Num(); ++i)
				{
					if (Units[i] != nullptr)
					{
						Units[i]->Warehouse = Hit.GetActor();
						Units[i]->ClickedRock = nullptr;
						Units[i]->ClickedTree = nullptr;
					}
				}
				SetPropertiesForSelectedUnits(Hit, false);
			}
			// need???????
			/*else if( Cast<AWalls>(Hit.GetActor()) && Hit.GetActor() != nullptr )
			{
				for (int i = 0; i < Units.Num(); ++i)
				{
					if (Units[i] != nullptr)
					{
						Units[i]->Wall = Hit.GetActor();
						Units[i]->ClickedRock = nullptr;
						Units[i]->ClickedTree = nullptr;
					}
				}
				SetPropertiesForSelectedUnits(Hit, false);
			}*/
			else if ( Hit.GetActor() != nullptr )	// walking to empty place
			{
				SetPropertiesForSelectedUnits(Hit, true);
			}
		}
	}
}

void APlayerCameraControllerPawn::MultiplySelection(float Value)
{
	if (Value )
		bMultiplySeletion = true;
	else
		bMultiplySeletion = false;
}