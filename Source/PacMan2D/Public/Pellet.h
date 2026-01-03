// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Pellet.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API APellet : public APaperFlipbookActor
{
	GENERATED_BODY()

	UPaperFlipbook* Flipbook;
	UPaperFlipbookComponent* FlipbookComponent;

public:
	APellet();
	const int Points = 10;

protected:
	virtual void BeginPlay() override;

private:
	void SetupFlipbook();
};
