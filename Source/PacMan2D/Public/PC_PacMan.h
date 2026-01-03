// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnhancedInputSubsystems.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_PacMan.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API APC_PacMan : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* PacManMappingContext;
	
};
