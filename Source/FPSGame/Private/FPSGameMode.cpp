// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"

AFPSGameMode::AFPSGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

    // use our custom HUD class
    HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn * InstigatorPawn)
{
    if (InstigatorPawn) {
        InstigatorPawn->DisableInput(nullptr);

        if (SpectatingViewpoint) {
            TArray<AActor *> Actors;
            UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, Actors);

            if (Actors.Num()) {
                AActor* NewViewTarget = Actors[0];

                APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
                if (PC) {
                    PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
                }
            }
        } else {
            UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpoing is null"));
        }
    }
    OnMissionCompleted(InstigatorPawn);
}

