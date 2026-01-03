// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pellet.h"
#include "BigPellet.h"
#include "Kismet/GameplayStatics.h"
#include "Ghost.h"


APacMan::APacMan() {
    bIsPoweredUp = false;
    PowerUpTime = 5.0f;
    bIsInvincible = false;
    Lives = 3;
    InvincibilityTime = 3.0f;
}

void APacMan::BeginPlay() {
    Super::BeginPlay();

    SetupMovementComponent();
    SetupFlipbookComponent();
    SetupCollisionComponent();
    GameMode = Cast<AGM_PacMan>(GetWorld()->GetAuthGameMode());
}

void APacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    UInputAction* MoveUpAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/InputAction_MoveUp.InputAction_MoveUp'"));
    EnhancedInput->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &APacMan::MoveUp);

    UInputAction* MoveRightAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/InputAction_MoveRight.InputAction_MoveRight'"));
    EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APacMan::MoveRight);

    UInputAction* MoveDownAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/InputAction_MoveDown.InputAction_MoveDown'"));
    EnhancedInput->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &APacMan::MoveDown);

    UInputAction* MoveLeftAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/InputAction_MoveLeft.InputAction_MoveLeft'"));
    EnhancedInput->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &APacMan::MoveLeft);
}

void APacMan::SetupMovementComponent() {
    MovementComponent = GetCharacterMovement();
    MovementComponent->MaxWalkSpeed = MAX_WALK_SPEED;
    MovementComponent->GroundFriction = 0.0f;
    MovementComponent->BrakingDecelerationWalking = 0.0f;

    MovementComponent->SetPlaneConstraintEnabled(true);
    MovementComponent->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
}

void APacMan::SetupFlipbookComponent() {
    FlipbookComponent = GetSprite();
    FlipbookComponent->SetWorldRotation(FRotator(180.0f, 0.0f, 90.0f));
}

void APacMan::SetupCollisionComponent() {
    CapsuleComponent = GetCapsuleComponent();
    CapsuleComponent->OnComponentHit.AddDynamic(this, &APacMan::OnHit);
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APacMan::OnOverlap);

    TagToCollisionLogic.Add(FName("TP_Left"), [this](AActor* OtherActor) {TP_LeftCollision(OtherActor);});
    TagToCollisionLogic.Add(FName("TP_Right"), [this](AActor* OtherActor) {TP_RightCollision(OtherActor);});
    TagToCollisionLogic.Add(FName("AddPelletScore"), [this](AActor* OtherActor) {PelletOverlap(OtherActor);});
    TagToCollisionLogic.Add(FName("TriggerPowerUp"), [this](AActor* OtherActor) {BigPelletOverlap(OtherActor);});
    TagToCollisionLogic.Add(FName("HandleGhostCollision"), [this](AActor* OtherActor) {GhostOverlap(OtherActor);});
}


void APacMan::MoveUp(const FInputActionValue& Value) {
    MovementComponent->Velocity = FVector(0.0f, 1.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 90.0f));
}

void APacMan::MoveRight(const FInputActionValue& Value) {
    MovementComponent->Velocity = FVector(-1.0f, 0.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetWorldRotation(FRotator(180.0f, 0.0f, 90.0f));
}

void APacMan::MoveDown(const FInputActionValue& Value) {
    MovementComponent->Velocity = FVector(0.0f, -1.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetWorldRotation(FRotator(0.0f, 270.0f, 90.0f));
}

void APacMan::MoveLeft(const FInputActionValue& Value) {
    MovementComponent->Velocity = FVector(1.0f, 0.0f, 0.0f) * MovementComponent->MaxWalkSpeed;
    FlipbookComponent->SetWorldRotation(FRotator(0.0f, 0.0f, 90.0f));
}


void APacMan::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    //UE_LOG(LogTemp, Warning, TEXT("Colliding with %s"), *(OtherActor->GetName()));
    MovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);

    for (const FName& Tag : OtherActor->Tags) {
        if (TFunction<void(AActor*)>* Func = TagToCollisionLogic.Find(Tag)) {
            (*Func)(OtherActor);
        }
    }
}

void APacMan::TP_LeftCollision(AActor* OtherActor) {
    SetActorLocation(FVector(950.0f, 42.5f, 30.0f), false, nullptr);
    FInputActionValue UnusedAnyway;
    MoveRight(UnusedAnyway);
}

void APacMan::TP_RightCollision(AActor* OtherActor) {
    SetActorLocation(FVector(-950.0f, 42.5f, 30.0f), false, nullptr);
    FInputActionValue UnusedAnyway;
    MoveLeft(UnusedAnyway);
}


void APacMan::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    //UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *(OtherActor->GetName()));
    for (const FName& Tag : OtherActor->Tags) {
        if (TFunction<void(AActor*)>* Func = TagToCollisionLogic.Find(Tag)) {
            (*Func)(OtherActor);
        }
    }
}

void APacMan::PelletOverlap(AActor* OtherActor) {
    APellet* Pellet = Cast<APellet>(OtherActor);
    GameMode->UpdateScore(Pellet->Points);
    Pellet->Destroy();
    UE_LOG(LogTemp, Warning, TEXT("Score is now %d"), GameMode->GetScore());
}

void APacMan::BigPelletOverlap(AActor* OtherActor) {
    ABigPellet* BigPellet = Cast<ABigPellet>(OtherActor);
    GameMode->UpdateScore(BigPellet->Points);
    ActivatePowerUp();
    BigPellet->Destroy();
    UE_LOG(LogTemp, Warning, TEXT("Score is now %d"), GameMode->GetScore());
}

void APacMan::ActivatePowerUp() {
    bIsPoweredUp = true;

    UWorld* World = GetWorld();
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(World, AGhost::StaticClass(), Actors);
    for (AActor* Actor : Actors) {
        AGhost* Ghost = Cast<AGhost>(Actor);
        Ghost->StartBeingScared();
    }

    MovementComponent->MaxWalkSpeed = EMPOWERED_MAX_WALK_SPEED;

    World->GetTimerManager().SetTimer(PowerUpTimerHandle, this, &APacMan::DeactivatePowerUp, PowerUpTime, false);
}

void APacMan::DeactivatePowerUp() {
    bIsPoweredUp = false;

    UWorld* World = GetWorld();
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(World, AGhost::StaticClass(), Actors);
    for (AActor* Actor : Actors) {
        AGhost* Ghost = Cast<AGhost>(Actor);
        Ghost->StopBeingScared();
    }

    MovementComponent->MaxWalkSpeed = MAX_WALK_SPEED;
}

void APacMan::GhostOverlap(AActor* OtherActor) {
    if (!bIsInvincible) {
        AGhost* Ghost = Cast<AGhost>(OtherActor);
        if (bIsPoweredUp) {
            GameMode->UpdateScore(Ghost->Points);
            Ghost->StartRespawn();
            UE_LOG(LogTemp, Warning, TEXT("Score is now %d"), GameMode->GetScore());
        }
        else {
            Lives--;
            if (Lives > 0) {
                UE_LOG(LogTemp, Warning, TEXT("PacMan has now %d lives. Invincibile for the next 3s..."), Lives);
                ActivateInvincibility();
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("PacMan is dead."));
                Destroy();
            }
        }
    }
}

void APacMan::ActivateInvincibility() {
    bIsInvincible = true;
    UWorld* World = GetWorld();
    World->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &APacMan::DeactivateInvincibility, InvincibilityTime, false);
}

void APacMan::DeactivateInvincibility() {
    bIsInvincible = false;
    UE_LOG(LogTemp, Warning, TEXT("PacMan is no more invincible."), Lives);
}