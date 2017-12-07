// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward delegations
class ATank;

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
    
    // starts tank moving barrel to shot where crosshair intersects the world.
    void AimTowardsCrossHair();

protected:
    
    UFUNCTION(BlueprintCallable, Category = "Tank")
    ATank* GetControlledTank() const;
    
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
