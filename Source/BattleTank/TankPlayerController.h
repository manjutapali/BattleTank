// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    
    void BeginPlay() override;
    
    void Tick(float DeltaTime) override;
    
    ATank* GetControlledTank() const;
    
    // starts tank moving barrel to shot where crosshair intersects the world.
    void AimTowardsCrossHair();
    
private:
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.3333;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
