// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement component"));
    ProjectileMovementComp->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::Launch(float speed)
{
    if(!ensure(ProjectileMovementComp)) { return; }
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Projectile firing at %f"), Time, speed)
    
    ProjectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
    ProjectileMovementComp->Activate();
}

