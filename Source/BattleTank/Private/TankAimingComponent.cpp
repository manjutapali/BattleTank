// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if(!Barrel) { return; }
    
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
        
        // move the barrel
        MoveBarrelTowards(AimDirection);
        
        auto Time = GetWorld()->GetTimeSeconds();
        
        UE_LOG(LogTemp, Warning, TEXT("%f :: Aiming with launch speed %f, AimDirection = %s"), Time, LaunchSpeed, *AimDirection.ToString());
    }
    else
    {
        auto Time = GetWorld()->GetTimeSeconds();
        
        UE_LOG(LogTemp, Warning, TEXT("%f :: No aiming solution found"), Time)
    }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Work out difference btwn current barrel direction and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
}

