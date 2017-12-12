// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("TankTrack beginplay"))
    OnComponentHit.AddDynamic(this, &UTankTrack::onHit);
}

void UTankTrack::onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
 
    UE_LOG(LogTemp, Warning, TEXT("Hitting"))
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    auto CorrectionAccelaration = -(SlippageSpeed / DeltaTime * GetRightVector());
    
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAccelaration / 2; // There are two tracks.
    
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
    auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    
}
