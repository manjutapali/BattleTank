// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    LastFireTime = FPlatformTime::Seconds();
}

void  UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    
    if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if(IsBarrelRotating())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Barrel is roatating"))
        FiringState = EFiringState::Aiming;
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("Locked State"))
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    
    if(!ensure(Barrel)) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                this,
                                OutLaunchVelocity,
                                StartLocation,
                                HitLocation,
                                LaunchSpeed,
                                false,
                                0,
                                0,
                                ESuggestProjVelocityTraceOption::DoNotTrace
                            );
    if(bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        CurrDirection = AimDirection;
        // move the barrel
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if(!ensure(Barrel) || !ensure(Turret)) { return; }
    // Work out difference btwn current barrel direction and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    
    Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
    if(FiringState != EFiringState::Reloading)
    {
        if(!ensure(Barrel) && !(ProjectileBlueprint)) { return; }
        // Spawning the Projectile actor
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                                              ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile"))
                                                              );
        
        // launch the projectile.
        Projectile->Launch(LaunchSpeed);
        
        LastFireTime = FPlatformTime::Seconds();
    }
}

bool UTankAimingComponent::IsBarrelRotating()
{
    if(!ensure(Barrel)) { return false; }
    
    auto BarrelForward = Barrel->GetForwardVector();
    
    UE_LOG(LogTemp, Warning, TEXT("Barrel forward = %s and Current Direction = %s"), *BarrelForward.ToString(), *CurrDirection.ToString())
    
    return !BarrelForward.Equals(CurrDirection, 0.01);
}
