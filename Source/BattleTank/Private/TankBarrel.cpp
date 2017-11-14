// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreePerSecond)
{
    UE_LOG(LogTemp, Warning, TEXT("Rotate barrel with roation speed = %f"), DegreePerSecond)
    // move barrel to right amount this frame
    // given max elevation speed, and the frame time
}


