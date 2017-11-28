// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle )
{
    UE_LOG(LogTemp, Warning, TEXT("Throttle value: %f"), throttle)
}
