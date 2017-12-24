// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);

        if(!ensure(PossessedTank)) { return; }

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPawnDeath);
    }
}

void ATankAIController::OnPawnDeath()
{
    GetPawn()->DetachFromControllerPendingDestroy();
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
        
        if(AimingComponent->GetFiringState() == EFiringState::Locked)
        {
            AimingComponent->Fire();
        }
        
    }
    
}





