// Fill out your copyright notice in the Description page of Project Settings.


#include "BigPellet.h"

#include "PaperFlipbookComponent.h"


ABigPellet::ABigPellet() {
    Flipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/Assets/Flipbooks/Items/BigPellet.BigPellet'"));
    FlipbookComponent = GetRenderComponent();
    FlipbookComponent->SetFlipbook(Flipbook);
}

void ABigPellet::BeginPlay() {
    Super::BeginPlay();
	SetupFlipbook();
}

void ABigPellet::SetupFlipbook() {
    SetActorRotation(FRotator(180.0f, 0.0f, 90.0f));
    FlipbookComponent->PlayFromStart();
}