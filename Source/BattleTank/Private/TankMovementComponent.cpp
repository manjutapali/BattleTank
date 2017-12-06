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
    
    auto Tankforward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIforward = MoveVelocity.GetSafeNormal();
    
    // Dot product to Get forward and backword movement to near the player tank.
    auto ForwardThrow = FVector::DotProduct(Tankforward, AIforward);
    
    // Cross product to get the direction for to move towards the player tank, Get Z vector.
    auto TurnThrow = FVector::CrossProduct(Tankforward, AIforward).Z;
    
    IntendToMoveForward(ForwardThrow);
    
    IntendMoveRight(TurnThrow);
    
    //UE_LOG(LogClass, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)
    
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

