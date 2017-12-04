// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::IntendToMoveForward(float Throw)
{
    UE_LOG(LogTemp, Warning, TEXT("Throttle value: %f"), Throw)
}

