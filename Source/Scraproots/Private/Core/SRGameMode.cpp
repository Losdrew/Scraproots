// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRGameMode.h"

#include "Core/SRGameplayEventRouter.h"

void ASRGameMode::BeginPlay()
{
	InitializeGameSystems();

	Super::BeginPlay();
}

void ASRGameMode::InitializeGameSystems()
{
	GameplayEventRouter = NewObject<USRGameplayEventRouter>(this);
	checkf(GameplayEventRouter, TEXT("GameplayEventRouter is not set in the SRGameMode!"));
}
