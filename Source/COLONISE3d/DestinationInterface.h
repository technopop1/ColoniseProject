// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestinationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDestinationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLONISE3D_API IDestinationInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DestinationChanged();
	
public:
};
