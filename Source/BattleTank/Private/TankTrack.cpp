// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::onHit);
}

void UTankTrack::onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
    DriveTrack();
    ApplySideWaysForce();
    CurrThrottle = 0;
}

void UTankTrack::ApplySideWaysForce()
{
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAccelaration = -(SlippageSpeed / DeltaTime * GetRightVector());
    
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAccelaration / 2; // There are two tracks.
    
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
    CurrThrottle = FMath::Clamp<float>(CurrThrottle + throttle, -1, +1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
