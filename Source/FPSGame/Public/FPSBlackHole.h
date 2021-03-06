// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AFPSBlackHole();

    virtual void Tick(float delta_time) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* inner_sphere;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* outer_sphere;


    UFUNCTION()
    void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    FVector center;
};
