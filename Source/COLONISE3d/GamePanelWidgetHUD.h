// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GamePanelWidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class COLONISE3D_API AGamePanelWidgetHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Wood = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stone = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Food = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Iron = 0;
};
