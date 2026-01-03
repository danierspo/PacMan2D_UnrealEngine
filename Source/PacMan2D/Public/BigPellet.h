// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbook.h"

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BigPellet.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API ABigPellet : public APaperFlipbookActor
{
	GENERATED_BODY()

	UPaperFlipbook* Flipbook;
	UPaperFlipbookComponent* FlipbookComponent;

public:
	ABigPellet();
	const int Points = 100;

protected:
	virtual void BeginPlay() override;

private:
	void SetupFlipbook();
};