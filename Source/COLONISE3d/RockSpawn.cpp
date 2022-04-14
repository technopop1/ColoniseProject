// Fill out your copyright notice in the Description page of Project Settings.


#include "RockSpawn.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARockSpawn::ARockSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rock"));
	RootComponent = Rock;
	
	FString Path = "";
	FMath::GetRandSeed();
	FMath Los;
	switch (Los.RandRange(0, 2))
	{
	case(0):
		Path = TEXT("/Game/Blends/Stone.Stone");
		break;
	case(1):
		Path = TEXT("/Game/Blends/Gold.Gold");
		break;
	case(2):
		Path = TEXT("/Game/Blends/Copper.Copper");
		break;
	default: 
		Path = TEXT("/Game/Blends/Stone.Stone");
		break;
	}

	//ConstructorHelpers::FObjectFinder<UStaticMesh> TreeAsset(*Path);
	if(ConstructorHelpers::FObjectFinder<UStaticMesh>(*Path).Succeeded())
	{
		Rock->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*Path).Object);
		Rock->SetRelativeRotation(FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f)); 
	}
	
	RockBox = CreateDefaultSubobject<UBoxComponent>("Box");
	RockBox->SetupAttachment(Rock);
	///// RockBox->SetHiddenInGame(false);
	RockBox->SetBoxExtent(FVector(500, 500, 300));
	RockBox->SetRelativeLocation(FVector(0,0,150));
	RockBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RockBox->SetGenerateOverlapEvents(true);
	RockBox->OnComponentBeginOverlap.AddDynamic(this, &ARockSpawn::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ARockSpawn::BeginPlay()
{
	Super::BeginPlay();
}

void ARockSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Cast<AUnitSpawn>(OtherActor)){
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("rockrockrockrock ")));
		AUnitSpawn* Unit = Cast<AUnitSpawn>(OtherActor);//->bGathering = true;
		Unit->bGathering = true;
	}
	//Units.Add(Cast<AUnitSpawn>(OtherActor));
	//Units.Last()->bGathering = true;
}

// Called every frame
void ARockSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

