// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize( UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity , bool bForceMaxSpeed)
{
    // No need to call super, since replacing the functionality.
    
    auto TankName = GetOwner()->GetName();
    auto MoveVelocityString = MoveVelocity.ToString();
    
    UE_LOG(LogClass, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)
    
}

void UTankMovementComponent::IntendToMoveForward(float Throw)
{
    if(!LeftTrack && !RightTrack) { return; }
    
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

