// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Function related to set the movement force to tank.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float throttle);
	
    // 40 tonne tank, force = mass * acc (considering acc = 10ms^-2)
    UPROPERTY(EditDefaultsOnly, Category = Input)
    float TrackMaxDrivingForce = 400000;

private:
    
    float CurrThrottle = 0;
    
    UTankTrack();
    
    void BeginPlay() override;
    
    void ApplySideWaysForce();
    
    void DriveTrack();
    
    UFUNCTION(BlueprintCallable, Category = "Track")
    void onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
};
