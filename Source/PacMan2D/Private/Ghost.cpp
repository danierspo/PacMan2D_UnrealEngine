// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"


AGhost::AGhost() {
    bIsScared = false;
    RespawnTime = 5.0f;
}

void AGhost::BeginPlay() {
    Super::BeginPlay();

    SetupMovementComponent();
    SetupFlipbookComponent();
    SetupAIComponent();
}

void AGhost::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    // Manage the AI in the EventTick instead of a more complicated approach with Behavior Trees
    TimeElapsed += DeltaTime;
    if (TimeElapsed >= 1.5f) {  // Every 1.5 seconds
        TimeElapsed = 0.0f;

        int Direction = FMath::RandRange(0, 3);
        switch (Direction) {
        case 0:
            MoveUp();
            break;
        case 1:
            MoveRight();
            break;
        case 2:
            MoveDown();
            break;
        case 3:
            MoveLeft();
            break;
        default:
            break;
        }
    }
}


void AGhost::SetupMovementComponent() {
    MovementComponent = GetCharacterMovement();
    MovementComponent->MaxWalkSpeed = 300.0f;
    MovementComponent->GroundFriction = 0.0f;
    MovementComponent->BrakingDecelerationWalking = 0.0f;

    MovementComponent->SetPlaneConstraintEnabled(true);
    MovementComponent->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
}

void AGhost::SetupFlipbookComponent() {
    FlipbookComponent = GetSprite();
    FlipbookComponent->SetWorldRotation(FRotator(180.0f, 0.0f, 90.0f));
}


// For more complicated AI, check this video: https://www.youtube.com/watch?v=ataGotQ7ir8
void AGhost::SetupAIComponent() {
    TimeElapsed = 0.0f;
}

void AGhost::MoveUp() {
    MovementComponent->Velocity = FVector(0.0f, 1.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetFlipbook(LookingUpFlipbook);
}

void AGhost::MoveRight() {
    MovementComponent->Velocity = FVector(-1.0f, 0.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetFlipbook(LookingRightFlipbook);
}

void AGhost::MoveDown() {
    MovementComponent->Velocity = FVector(0.0f, -1.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetFlipbook(LookingDownFlipbook);
}

void AGhost::MoveLeft() {
    MovementComponent->Velocity = FVector(1.0f, 0.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetFlipbook(LookingLeftFlipbook);
}

void AGhost::StartBeingScared() {
    SetActorTickEnabled(false);
    MovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
    FlipbookComponent->SetFlipbook(ScaredFlipbook);
}

void AGhost::StopBeingScared() {
    SetActorTickEnabled(true);
}

void AGhost::StartRespawn() {
    UWorld* World = GetWorld();
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    World->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AGhost::EndRespawn, RespawnTime, false);
}

void AGhost::EndRespawn() {
    SetActorLocation(FVector(0.0f, 0.0f, 30.0f));
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
}