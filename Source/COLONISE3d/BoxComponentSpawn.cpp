// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxComponentSpawn.h"
#include "Components/BoxComponent.h"


// Sets default values
ABoxComponentSpawn::ABoxComponentSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// UBoxComponent
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("Box Collision"); //ATriggerVolume
	RootComponent = TriggerVolume;
	TriggerVolume->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ABoxComponentSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxComponentSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

