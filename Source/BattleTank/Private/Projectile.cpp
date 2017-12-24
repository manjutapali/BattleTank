// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    CollissionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collssion Mesh"));
    SetRootComponent(CollissionMesh);
    CollissionMesh->SetNotifyRigidBodyCollision(true);
    CollissionMesh->SetVisibility(true);
    
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    
    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement component"));
    ProjectileMovementComp->bAutoActivate = false;
    
    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate  = false;
    
    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollissionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float speed)
{
    if(!ProjectileMovementComp) { return; }
    auto Time = GetWorld()->GetTimeSeconds();
    
    ProjectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
    ProjectileMovementComp->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
    SetRootComponent(ImpactBlast);
    CollissionMesh->DestroyComponent();
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();
    
    UGameplayStatics::ApplyRadialDamage(this, TankDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
    
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectile, DestroyDelay, false);

}

void AProjectile::DestroyProjectile()
{
    Destroy();
}
