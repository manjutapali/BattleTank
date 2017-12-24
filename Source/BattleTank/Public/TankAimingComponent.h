// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    NoAmmo
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
    
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetRoundsLeft() const;
    
protected:
    
    UPROPERTY(BlueprintReadOnly, Category = "UI")
    EFiringState FiringState = EFiringState::Reloading;
    
private:
    UTankBarrel* Barrel = nullptr;
    
    UTankTurret* Turret = nullptr;
    
    FVector CurrDirection = FVector();
    
    double LastFireTime = 0;
    
   
    
    void MoveBarrelTowards(FVector AimDirection);
    
    virtual void BeginPlay();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
    
    bool IsBarrelRotating();
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 4000.0;
    
    UPROPERTY(EditDefaultsOnly,Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 RoundsLeft = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
};
