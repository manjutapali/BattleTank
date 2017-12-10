// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Delgation
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
    
    UFUNCTION(BlueprintCallable, Category = "Tank")
    void Fire();

private:
    
    virtual void BeginPlay();
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly,Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 4000.0;
    
    // Barrel reference
    UTankBarrel* Barrel = nullptr; // TODO Remove
    
    double LastFireTime = 0;
};
