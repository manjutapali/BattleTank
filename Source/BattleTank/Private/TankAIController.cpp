// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No AI controlled Tank"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI controlled Tank = %s"), *(ControlledTank->GetName()))
    }
    
    auto PlayerTank = GetPlayerTank();
    
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank is not found"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank is = %s"), *(PlayerTank->GetName()))
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(GetPlayerTank())
    {
        AimToPlayer(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(!PlayerTank)
    {
        return nullptr;
    }
    else
    {
        return Cast<ATank>(PlayerTank);
    }
}
void ATankAIController::AimToPlayer(FVector HitLocation)
{
    GetControlledTank()->AimAt(HitLocation);
}



