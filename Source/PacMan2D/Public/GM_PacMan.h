// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_PacMan.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN2D_API AGM_PacMan : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_PacMan();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Score")
	int Score;
	UFUNCTION(BlueprintCallable, Category = "Score")
	int UpdateScore(int Points);
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore() const;
};
