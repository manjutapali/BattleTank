// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

// Forward delagtions
class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
    // Overriding the actor begin play in the parent list.
    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaTime);
    
    void AimToPlayer(FVector HitLocation);
    
    
private:
    ATank* GetControlledTank() const;
    
    ATank* GetPlayerTank() const;
};
