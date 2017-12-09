// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    
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

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
    //UE_LOG(LogClass, Warning, TEXT("Aiming towards cross hair"))
    
    if(!GetControlledTank()) { return; }
    
    FVector HitLocation; //out parameter;

    if(GetSightRayHitLocation(HitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Hit location - %s"), *HitLocation.ToString());
        
        GetControlledTank()->AimAt(HitLocation);
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
        //UE_LOG(LogTemp, Warning, TEXT("Look direction is %s"), *LookDirection.ToString())
        
        // Line trace along that look direction and see what it hits.
        
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    
    //HitLocation = FVector(1.0);
    return true;
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
        ECollisionChannel::ECC_Visibility)
       )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}
