// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "InputAction.h"
#include "GM_PacMan.h"

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PacMan.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API APacMan : public APaperCharacter
{
	GENERATED_BODY()

    UCharacterMovementComponent* MovementComponent;
    UPaperFlipbookComponent* FlipbookComponent;
    UCapsuleComponent* CapsuleComponent;
    TMap<FName, TFunction<void(AActor*)>> TagToCollisionLogic;

    AGM_PacMan* GameMode;

    const float MAX_WALK_SPEED = 300.0f;
    const float EMPOWERED_MAX_WALK_SPEED = 600.0f;

    bool bIsPoweredUp;
    float PowerUpTime;
    FTimerHandle PowerUpTimerHandle;

    int Lives;
    bool bIsInvincible;
    float InvincibilityTime;
    FTimerHandle InvincibilityTimerHandle;

	
protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

public:
    APacMan();
    void MoveUp(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
    void MoveDown(const FInputActionValue& Value);
    void MoveLeft(const FInputActionValue& Value);

private:
    void SetupMovementComponent();
    void SetupFlipbookComponent();
    void SetupCollisionComponent();

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    void TP_LeftCollision(AActor* OtherActor);
    void TP_RightCollision(AActor* OtherActor);

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    void PelletOverlap(AActor* OtherActor);
    void BigPelletOverlap(AActor* OtherActor);
    void ActivatePowerUp();
    void DeactivatePowerUp();
    void GhostOverlap(AActor* OtherActor);
    void ActivateInvincibility();
    void DeactivateInvincibility();
};