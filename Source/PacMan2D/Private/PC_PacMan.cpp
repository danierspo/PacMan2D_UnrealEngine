// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_PacMan.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void APC_PacMan::BeginPlay() {
	Super::BeginPlay();

	PacManMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/PacManMovement.PacManMovement'"));
	if (PacManMappingContext) {
		if (ULocalPlayer* localPlayer = GetLocalPlayer()) {
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
				InputSubsystem->AddMappingContext(PacManMappingContext, 0);
			}
		}
	}
}