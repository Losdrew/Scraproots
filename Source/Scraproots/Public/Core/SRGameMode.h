// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SRGameMode.generated.h"

class USRGameplayEventRouter;

UCLASS()
class SCRAPROOTS_API ASRGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual USRGameplayEventRouter* GetGameplayEventRouter() const { return GameplayEventRouter; }
	
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay Events")
	TObjectPtr<USRGameplayEventRouter> GameplayEventRouter;

private:
	void InitializeGameSystems();
};