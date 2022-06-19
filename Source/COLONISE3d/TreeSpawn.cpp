// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawn.h"

//#include "Editor.h"
#include "EngineUtils.h"
#include "UnitSpawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"
//#include "Editor/EditorEngine.h"


// Sets default values
ATreeSpawn::ATreeSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree"));
	RootComponent = Tree;
	//Tree->SetupAttachment(RootComponent);
	
	FString Path;
	FMath::GetRandSeed();
	FMath Los;
	switch (Los.RandRange(0, 3))
	{
	case(0):
		Path = TEXT("/Game/Blends/Tree_00.Tree_00"); //MyTrees/ // /MyTrees
		//TreeScaleValue = 1.0;                      //         
		break;                                       //         
	case(1):                                         //         
		Path = TEXT("/Game/Blends/Tree_01.Tree_01"); //MyTrees/ 
		//TreeScaleValue = 0.7;                      //         
		break;                                       //         
	case(2):                                         //         
		Path = TEXT("/Game/Blends/Tree_02.Tree_02"); //MyTrees/ 
		//TreeScaleValue = 0.85;                     //         
		break;                                       //         
	/*case(3):                                     //         
		Path = TEXT("/Game/Blends/Tree_03.Tree_03"); //MyTrees/ 
		//TreeScaleValue = 0.85;                     //         
		break;            */                           //         
	default:                                         //         
		Path = TEXT("/Game/Blends/Tree_00.Tree_00"); //MyTrees/ 
		//TreeScaleValue = 1.0;
		break;
	}

	//ConstructorHelpers::FObjectFinder<UStaticMesh> TreeAsset(*Path);
	if(ConstructorHelpers::FObjectFinder<UStaticMesh>(*Path).Succeeded())
	{
		Tree->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*Path).Object);
		Tree->SetRelativeRotation(FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f));
		Tree->Mobility = EComponentMobility::Static;
		//Tree->SetRelativeScale3D(FVector(1.0, 1.0, TreeScaleValue ));	// scale because of huge size of imported trees
	}
	
	TreeBox = CreateDefaultSubobject<UBoxComponent>("Box");
	TreeBox->SetupAttachment(Tree);
	/////// TreeBox->SetHiddenInGame(false);
	TreeBox->SetBoxExtent(FVector(250, 250, 300));
	TreeBox->SetRelativeLocation(FVector(0,0,150));
	TreeBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TreeBox->SetGenerateOverlapEvents(true);
	TreeBox->OnComponentBeginOverlap.AddDynamic(this, &ATreeSpawn::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATreeSpawn::BeginPlay()
{
	Super::BeginPlay();

}
void ATreeSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Cast<AUnitSpawn>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("33333333333 ")));
		AUnitSpawn* Unit = Cast<AUnitSpawn>(OtherActor);//->bGathering = true;
		Unit->bGathering = true;
	}
	//Units.Add(Cast<AUnitSpawn>(OtherActor));
	//Units.Last()->bGathering = true;
}

// Called every frame
void ATreeSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

