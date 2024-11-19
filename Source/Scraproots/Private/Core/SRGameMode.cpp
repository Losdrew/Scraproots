// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRGameMode.h"

#include "Core/SRGameplayEventRouter.h"
#include "Inventory/SRInventoryManager.h"
#include "Product/SRProductManager.h"

void ASRGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameSystems();
}

void ASRGameMode::InitializeGameSystems()
{
	GameplayEventRouter = NewObject<USRGameplayEventRouter>(this);
	checkf(GameplayEventRouter, TEXT("GameplayEventRouter is not set in the SRGameMode!"));

	ProductManager = NewObject<USRProductManager>(this);
	checkf(ProductManager, TEXT("ProductManager is not set in the SRGameMode!"));
	if (ProductManager)
	{
		ProductManager->Initialize(ProductsConfig);
	}

	InventoryManager = NewObject<USRInventoryManager>(this);
	checkf(InventoryManager, TEXT("InventoryManager is not set in the SRGameMode!"));
	if (InventoryManager)
	{
		InventoryManager->Initialize();
	}
}
