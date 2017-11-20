// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    
    auto RotationChange = RelativeSpeed * MaxDegreesRotationPerSecond * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = RelativeRotation.Yaw + RotationChange;
    // auto DeltaRotation = FMath::Clamp(RawNewRotation, MinDegreeRotation, MaxDegreeRoation);
    
    //UE_LOG(LogTemp, Warning, TEXT("Delta Roation = %f"), NewRotation);
    
    SetRelativeRotation(FRotator(0, NewRotation, 0));
    
}
