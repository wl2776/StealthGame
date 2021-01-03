// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    RootComponent = MeshComp;
    sphere_comp1 = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("sphere"));

    sphere_comp1->SetupAttachment(MeshComp);
    sphere_comp1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    sphere_comp1->SetCollisionResponseToAllChannels(ECR_Ignore);
    sphere_comp1->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    sphere_comp1->AddForce();

}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
    Super::BeginPlay();
    
}


void AFPSBlackHole::Tick()
{
    TSet<UPrimitiveComponent *> comps;
    sphere_comp1->GetOverlappingComponents(comps);

    for (auto& c : comps) {
        c->DestroyComponent(true);
    }
}
