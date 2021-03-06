// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    
    UFUNCTION(BlueprintCallable, Category = "Tank Movement")
    void Initialize( UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendToMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveRight(float Throw);
    
private:
    
    // Called by AI Controller.
    void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    
    UTankTrack* LeftTrack = nullptr;
    
    UTankTrack* RightTrack = nullptr;
	
};
