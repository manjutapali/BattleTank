// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward delegations
class UTankAimingComponent;

/**
 * Contains function related user play.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    
    void BeginPlay() override;
    
    void Tick(float DeltaTime) override;
    
    void SetPawn(APawn* InPawn) override;

    // starts tank moving barrel to shot where crosshair intersects the world.
    void AimTowardsCrossHair();

protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void AimingComponentFound(UTankAimingComponent* AimingComponent);
    
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

    UFUNCTION()
    void OnPlayerDeath();
};
