// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if(BarrelToSet)
    {
        TankAimingComponent->SetBarrelReference(BarrelToSet);
        Barrel = BarrelToSet;
    }
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    if(TurretToSet)
        TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
    auto Time = GetWorld()->GetTimeSeconds();
    //UE_LOG(LogTemp, Warning, TEXT("%f : Firing the projectile"), Time)
    
    if(!Barrel) { return; }
    
    GetWorld()->SpawnActor<AProjectile>(
                                        ProjectileBlueprint,
                                        Barrel->GetSocketLocation(FName("Projectile")),
                                        Barrel->GetSocketRotation(FName("Projectile"))
                                        );
}
