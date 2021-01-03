// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    outer_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("field"));
    outer_sphere->SetSphereRadius(15000);
    outer_sphere->SetupAttachment(MeshComp);

    inner_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("hole"));
    inner_sphere->SetSphereRadius(100);
    inner_sphere->SetupAttachment(outer_sphere);
    inner_sphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphere);

    RootComponent = MeshComp;
}

void AFPSBlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor) {
        OtherActor->Destroy();
    }

}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
    Super::BeginPlay();
    
    center = GetActorLocation();
}

void AFPSBlackHole::Tick(float delta_time)
{
    Super::Tick(delta_time);
    TArray<UPrimitiveComponent *> comps;
    outer_sphere->GetOverlappingComponents(comps);

    const float radius = outer_sphere->GetScaledSphereRadius();
    const float strength = -2000.f;

    if (comps.Num()) {
        for (auto& c : comps) {
            if(c->IsSimulatingPhysics())
                c->AddRadialForce(center, radius, strength, ERadialImpulseFalloff::RIF_Constant, true);
        }
    }

    //inner_sphere->GetOverlappingComponents(comps);
    //if (comps.Num()) {
    //    for (auto& c : comps) {
    //        if(c != outer_sphere)
    //            c->DestroyComponent(true);
    //    }
    //}
}

