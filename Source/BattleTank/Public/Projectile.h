// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    void Launch(float speed);
private:
    
    UProjectileMovementComponent* ProjectileMovementComp = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    float DestroyDelay = 10.0f;
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    float TankDamage = 20.0f;
    
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* CollissionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category="Components")
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category="Components")
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category="Components")
    URadialForceComponent* ExplosionForce = nullptr;
    
    void DestroyProjectile();
    
    UFUNCTION(BlueprintCallable, Category = "Track")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
};
