// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

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

    virtual void SetPawn(APawn* InPawn) override;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AccepatceRadius = 80000;

private:

    UFUNCTION()
    void OnPawnDeath();
    
};
