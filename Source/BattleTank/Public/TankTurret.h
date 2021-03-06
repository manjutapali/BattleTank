// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
// Turret related functions.
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    
    void Rotate(float RelativeSpeed);

private:
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxDegreesRotationPerSecond = 5;
    
  	UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MaxDegreeRoation = 225;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float MinDegreeRotation = 0;
};
