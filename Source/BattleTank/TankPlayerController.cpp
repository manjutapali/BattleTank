// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing tank"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing tank, tank = %s"), *(ControlledTank->GetName()))
    }
    //UE_LOG(LogTemp, Warning, TEXT("Begin play in tankplayer controller"));
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
        UE_LOG(LogTemp, Warning, TEXT("Hit location - %s"), *HitLocation.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const // True if hits Landscape.
{
    // Find the cross hair projection
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    //UE_LOG(LogClass, Warning, TEXT("Screen location : %s"), *ScreenLocation.ToString())
    // de-project the screen position of cross hair into world direction
    // Line trace along that look direction and see what it hits.
    //HitLocation = FVector(1.0);
    return true;
}
