// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
// Barrel related functions
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    
    // values takes -1 to 1, to move the barrel in the direction
    void Elevate(float RelativeSpeed);

private:
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxDegreesPerSecond = 5;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxElevationDegree = 40;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MinElevationDegree = 0;
    
};
