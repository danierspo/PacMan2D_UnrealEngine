// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API AGhost : public APaperCharacter
{
    GENERATED_BODY()

    UCharacterMovementComponent* MovementComponent;
    UPaperFlipbookComponent* FlipbookComponent;
    float TimeElapsed;
    bool bIsScared;

    float RespawnTime;
    FTimerHandle RespawnTimerHandle;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
    UPaperFlipbook* LookingUpFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
    UPaperFlipbook* LookingRightFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
    UPaperFlipbook* LookingDownFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
    UPaperFlipbook* LookingLeftFlipbook;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
    UPaperFlipbook* ScaredFlipbook;

    const int Points = 100;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    AGhost();
    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void StartBeingScared();
    void StopBeingScared();
    void StartRespawn();
    void EndRespawn();

private:
    void SetupMovementComponent();
    void SetupFlipbookComponent();
    void SetupAIComponent();
};
