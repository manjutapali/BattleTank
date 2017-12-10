// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(ensure(PlayerTank))
    {
        MoveToActor(PlayerTank, AccepatceRadius);
        
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
        
        //GetPawn()->Fire();
    }
    
}




