// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

#include "FPSExtractionZone.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
    OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoverlapComp"));
    OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    OverlapComp->SetBoxExtent(FVector(200.0f));

    RootComponent = OverlapComp;
    OverlapComp->SetHiddenInGame(false);
    OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

    DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
    DecalComp->DecalSize = { 200.0f, 200.0f, 200.0f };
    DecalComp->SetupAttachment(RootComponent);
}


void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    UE_LOG(LogTemp, Log, TEXT("Overlapped!"));
    AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
    if (MyPawn && MyPawn->bIsCarryingObjective) {
        AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
        if (GM) {
            GM->CompleteMission(MyPawn);
        }
    }
}
