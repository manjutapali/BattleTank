// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // move barrel to right amount this frame
    // given max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}


