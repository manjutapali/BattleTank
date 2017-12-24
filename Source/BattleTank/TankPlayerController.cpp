// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if(ensure(AimingComponent))
    {
        AimingComponentFound(AimingComponent);
    }
    
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrossHair();
}

void ATankPlayerController::SetPawn(APawn *InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        auto PlayerTank = Cast<ATank>(InPawn);
        
        PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerDeath);
    }
}

void ATankPlayerController::OnPlayerDeath()
{
    StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if(!GetPawn()) { return; }
    
    FVector HitLocation; //out parameter;

    if(GetSightRayHitLocation(HitLocation))
    {
        auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const // True if hits Landscape.
{
    // Find the cross hair projection
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    //UE_LOG(LogClass, Warning, TEXT("Screen location : %s"), *ScreenLocation.ToString())
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line trace along that look direction and see what it hits.
        
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    // de-project the screen position of cross hair into world direction
    FVector CameraWorldLocation;
    FVector WorldDirection;
    
    bool result = DeprojectScreenPositionToWorld(
                                   ScreenLocation.X,
                                   ScreenLocation.Y,
                                   CameraWorldLocation,
                                   LookDirection);
    
    return result;
    
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + ( LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Camera)
       )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}
