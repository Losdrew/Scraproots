// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SRGameMode.generated.h"

UCLASS()
class SCRAPROOTS_API ASRGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};