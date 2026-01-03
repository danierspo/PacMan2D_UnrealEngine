// Fill out your copyright notice in the Description page of Project Settings.


#include "Pellet.h"

#include "PaperFlipbookComponent.h"


APellet::APellet() {
    Flipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Flipbooks/Items/Pellet_Flipbook.Pellet_Flipbook'"));
    FlipbookComponent = GetRenderComponent();
    FlipbookComponent->SetFlipbook(Flipbook);
}

void APellet::BeginPlay() {
    Super::BeginPlay();
    SetupFlipbook();
}

void APellet::SetupFlipbook() {
    SetActorRotation(FRotator(180.0f, 0.0f, 90.0f));
    FlipbookComponent->PlayFromStart();
}