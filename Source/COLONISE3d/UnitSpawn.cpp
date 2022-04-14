// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawn.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "RockSpawn.h"
#include "TreeSpawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUnitSpawn::AUnitSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("NoName"));
	//RootComponent = MyRoot;
	GetCapsuleComponent()->SetupAttachment(MyRoot);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 88.0));
	GetCapsuleComponent()->SetRelativeLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z+185.0));
	GetMesh()->SetRelativeLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z-90.0));
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1.35, 1.35, 2));
	
	
	// Save animations
	FString Path = "/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin";
	if(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*Path).Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*Path).Object);
	}
	Path = "AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'";
	if(ConstructorHelpers::FObjectFinder<UAnimBlueprint>(*Path).Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ConstructorHelpers::FObjectFinder<UAnimBlueprint>(*Path).Object->GeneratedClass);
	}
}

// Called when the game starts or when spawned
void AUnitSpawn::BeginPlay()
{
	Super::BeginPlay();
	
	// in future it should be Tarray of warehouse if it is possible to create new smalls warehouses
	Warehouse = UGameplayStatics::GetActorOfClass(AActor::GetWorld(), TSubclassOf<AMainWarehouseSpawn>( AMainWarehouseSpawn::StaticClass() ) );
	
}

void AUnitSpawn::MoveUnit(float DeltaTime)
{
	FVector MyLoc = GetActorLocation();
	//FVector NewLoc = UKismetMathLibrary::VInterpTo_Constant(MyLoc, Destination, DeltaTime, 250);
	//SetActorLocation(NewLoc);
	Destination.Z = MyLoc.Z;	// need to make "move to location" to work correctly
	if (bIfTree)
	{
		if (FVector::Dist(MyLoc, Destination) <= 350)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("TAUFHIFHSDYFSDIFH")));
			bIfTree = false;
			bUnitMove = false;
		}
	}
	else if (bIfRock)
	{
		if (FVector::Dist(MyLoc, Destination) <= 550)
		{
			bIfRock = false;
			bUnitMove = false;
		}
	}
	else if (bIfWarehouse)
	{
		if (FVector::Dist(MyLoc, Destination) <= 750)
		{
			bIfWarehouse = false;
			bUnitMove = false;
			if(ClickedTree != nullptr && ClickedTree->bIsAlive)
			{
				SetPropertiesForSelectedUnit(ClickedTree);
			}
			else if(ClickedRock != nullptr && ClickedRock->bIsAlive)
			{
				SetPropertiesForSelectedUnit(ClickedRock);
			}
		}
	}
	else
	{
		if (FVector::Dist(MyLoc, Destination) <= 50)
		{
			bUnitMove = false;
		}
	}
}
void AUnitSpawn::SetPropertiesForSelectedUnit(FHitResult Hit, const bool bEmptyPlaceLocation, FVector NewPos)
{
	Destination = Hit.Location.operator+(NewPos);
	bUnitMove = true;											// while true unit will move to object
	bSelected = false;											// is false you can't give this unit an order
}

void AUnitSpawn::SetPropertiesForSelectedUnit(FHitResult Hit, const bool bEmptyPlaceLocation)
{
	if (!bEmptyPlaceLocation)									// check if object was clicked or just ground was clicked to choose place destination
	{
		Destination = Hit.GetActor()->GetActorLocation();		// set location of gatherable object
	}
	else
	{
		Destination = Hit.Location;
	}
	if (Hit.GetActor()->GetName().Contains("Tree") )		// if tree was clicked, then bIfTree = true, then unit walks to the tree allowed distance	
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("TAUFHIFHSaaaaaaaaaaaaaaaaaaaaaaaaaDYFSDIFH")));
		bIfTree = true;						// if true, unit walks to set distance of Tree
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-350.0f, 350.0f), FMath::FRandRange(-350.0f, 350.0f), 0.0);	// randomize positon od destination
		Destination = Hit.GetActor()->GetActorLocation().operator+=(CloseRandDestination);					
	}
	else if (Hit.GetActor()->GetName().Contains("Rock") )
	{
		bIfRock = true;						// if true, unit walks to set distance of Tree
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-550.0f, 550.0f), FMath::FRandRange(-550.0f, 550.0f), 0.0);
		Destination = Hit.GetActor()->GetActorLocation().operator+=(CloseRandDestination);					
	}
	else if (Hit.GetActor()->GetName().Contains("Warehouse") )
	{
		bIfWarehouse = true;				// if true, unit walks to set distance of Tree
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-750.0f, 750.0f), FMath::FRandRange(-750.0f, 750.0f), 0.0);
		Destination = Hit.GetActor()->GetActorLocation().operator+=(CloseRandDestination);					
	}
	bUnitMove = true;											// while true unit will move to object
	bSelected = false;											// is false you can't give this unit an order
	//Units[i]->MoveUnit();
}
void AUnitSpawn::SetPropertiesForSelectedUnit(AActor* Object)
{
	//Destination = Object->GetTargetLocation();		// set location of gatherable object
	if (Object->GetName().Contains("Tree") )		// if tree was clicked, then bIfTree = true, then unit walks to the tree allowed distance	
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("TAUFHIFHSDYFSDIFH")));
		bIfTree = true;											// if true, unit walks to set distance of Tree
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-350.0f, 350.0f), FMath::FRandRange(-350.0f, 350.0f), 0.0);
		Destination = Object->GetTargetLocation().operator+=(CloseRandDestination);
	}
	else if (Object->GetName().Contains("Rock") )
	{
		bIfRock = true;
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-550.0f, 550.0f), FMath::FRandRange(-550.0f, 550.0f), 0.0);
		Destination = Object->GetTargetLocation().operator+=(CloseRandDestination);
	}
	else if (Object->GetName().Contains("Warehouse") )
	{
		bIfWarehouse = true;
		const FVector CloseRandDestination = FVector(FMath::FRandRange(-750.0f, 750.0f), FMath::FRandRange(-750.0f, 750.0f), 0.0);
		Destination = Object->GetTargetLocation().operator+=(CloseRandDestination);
	}
	bUnitMove = true;											// while true unit will move to object
	bSelected = false;											// is false you can't give this unit an order
	//Units[i]->MoveUnit();
}
void AUnitSpawn::ReachedLimit()
{
	Destination = Warehouse->GetActorLocation();
	bIfWarehouse = true;
	bUnitMove = true;
}
void AUnitSpawn::StopUnit()
{
	 bSelected = false;					// Unit selection state
     bUnitMove = false;					// Unit movement state
     bIfTree = false;					// Unit tree clicked state
     bIfRock = false;					// Unit rock clicked state
     bIfWarehouse = false;					// Unit warehouse clicked state
     bGathering = false;
}
void AUnitSpawn::AddResource()
{
	/// POPRAWIC KOD - ZEBY NIE ROZDZIELAC NA 2 IFy
	if(ClickedTree != nullptr)
	{
		if (ClickedTree->SecondsOfGathering >= 1.0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("abababababaabababababab %f"),UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
			Wood += GatheringSpeed;
			ClickedTree->TreeLimit -= GatheringSpeed;
			if (ClickedTree->TreeLimit <= 0 ){
				StopUnit();
				ClickedTree->bIsAlive = false;
				ClickedTree->Destroy();
				ReachedLimit();
				//ClickedTree = nullptr;
			}
			if (Wood == Limit ) //|| ClickedTree == nullptr)
			{
				ReachedLimit();
			}
			ClickedTree->SecondsOfGathering = 0.0;
		}
		else
		{
			ClickedTree->SecondsOfGathering += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		}
	}
	else if(ClickedRock != nullptr)
	{
		if (ClickedRock->SecondsOfGathering >= 1.0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("35654yrthdfgfgfg %f"),UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
			Stone += GatheringSpeed;
			ClickedRock->RockLimit -= GatheringSpeed;
			if (ClickedRock->RockLimit <= 0 ){
				StopUnit();
				ClickedRock->bIsAlive = false;
				ClickedRock->Destroy();
				ReachedLimit();
				//ClickedRock = nullptr;
			}
			if (Stone == Limit )//|| ClickedRock == nullptr)
			{
				ReachedLimit();
			}
			ClickedRock->SecondsOfGathering = 0.0;
		}
		else
		{
			ClickedRock->SecondsOfGathering += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		}
	}
}

void AUnitSpawn::CheckDestState()  // should stop all units which want to gather if destination object was destroyed... should...
{
	if (bIfTree && !ClickedTree->bIsAlive)
		StopUnit();
	if (bIfRock && !ClickedRock->bIsAlive)
		StopUnit();
}

// Called every frame
void AUnitSpawn::Tick(float DeltaTime)
{
	if (!bUnitMove && bGathering && ClickedTree != nullptr && ClickedTree->TreeBox->IsOverlappingActor(this))
	{
		AddResource();
	}
	else if (bGathering && bIfTree && !ClickedTree)
	{
		ReachedLimit();
	}
	else if (!bUnitMove && bGathering && ClickedRock != nullptr && ClickedRock->RockBox->IsOverlappingActor(this))
	{
		AddResource();
	}
	//if ((Wood > 0 || Stone > 0) && bGathering && ClickedRock == nullptr) ReachedLimit(); // if unit was gathering and object destroyed
	if (bUnitMove) {
		MoveUnit(DeltaTime);
		if (bIfTree || bIfRock)
			CheckDestState();
	}
	if (Health <= 0)
	{
		Destroy();
	}

	
	
	Super::Tick(DeltaTime);

}