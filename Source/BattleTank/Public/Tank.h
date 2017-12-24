// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
    
    // Called by the engine, when actor meets daamge force.
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
    
    // Returns percentage health of the tank between 0 to 1.
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercentage() const;
    
private:
    
    virtual void BeginPlay();
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    int32 StartingHealth = 100;
    
    UPROPERTY(VisibleAnywhere, Category="Health")
    int32 CurrentHealth = StartingHealth;
    
};
