// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward Delgation
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds functions related to aiming the barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    UFUNCTION(BlueprintCallable, Category = "Tank Aiming")
    void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = "Tank")
    void Fire();
    
protected:
    
    UPROPERTY(BlueprintReadOnly, Category = "UI")
    EFiringState FiringState = EFiringState::Aiming;
    
private:
    UTankBarrel* Barrel = nullptr;
    
    UTankTurret* Turret = nullptr;
    
    double LastFireTime = 0;
    
    void MoveBarrelTowards(FVector AimDirection);
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 4000.0;
    
    UPROPERTY(EditDefaultsOnly,Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
};
