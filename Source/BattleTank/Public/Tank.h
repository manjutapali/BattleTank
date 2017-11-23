// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Delgation
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = Tank)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = Tank)
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Tank)
    void Fire();
    
protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 100000.0; // TODO, Get the proper velocity
    
    UPROPERTY(EditDefaultsOnly,Category = Firing)
    float ReloadTimeInSeconds = 3;
    
    // Barrel reference
    UTankBarrel* Barrel = nullptr;
    
    double LastFireTime = 0;
};
