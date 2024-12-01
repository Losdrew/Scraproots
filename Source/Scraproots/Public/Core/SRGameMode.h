// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Product/SRProductTypes.h"
#include "SRGameMode.generated.h"

class USRGameplayEventRouter;
class USRProductManager;
class USRInventoryManager;

UCLASS()
class SCRAPROOTS_API ASRGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual USRGameplayEventRouter* GetGameplayEventRouter() const { return GameplayEventRouter; }
	virtual USRProductManager* GetProductManager() const { return ProductManager; }
	virtual USRInventoryManager* GetInventoryManager() const { return InventoryManager; }
	
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay Events")
	TObjectPtr<USRGameplayEventRouter> GameplayEventRouter;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Product")
	TObjectPtr<USRProductManager> ProductManager;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Inventory Manager")
	TObjectPtr<USRInventoryManager> InventoryManager;

private:
	void InitializeGameSystems();
};