// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_PacMan.h"

AGM_PacMan::AGM_PacMan() {
	Score = 0;
}

int AGM_PacMan::UpdateScore(int Points) {
	return Score += Points;
}

int AGM_PacMan::GetScore() const {
	return Score;
}