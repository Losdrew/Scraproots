// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRStatics.generated.h"

struct FSRGameplayEvent;

/**
 * Static class with utility functions for the game.
 */
UCLASS(MinimalAPI)
class USRStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Gameplay Events", meta = (WorldContext = "WorldContextObject"))
	static class USRGameplayEventRouter* GetGameplayEventRouter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Events", meta = (WorldContext = "WorldContextObject"))
	static bool BroadcastGameplayEvent(const UObject* WorldContextObject, const FSRGameplayEvent& Event);

	// Searches the world's actors for one that matches the given object name.
	UFUNCTION(BlueprintPure, Category = "Utility", meta = (WorldContext = "WorldContextObject"))
	static AActor* FindActorByName(const UObject* WorldContextObject, const FString& ObjectName);

	UFUNCTION(BlueprintPure, Category = "Managers", meta = (WorldContext = "WorldContextObject"))
	static class USRProductManager* GetProductManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Managers", meta = (WorldContext = "WorldContextObject"))
	static class USRInventoryManager* GetInventoryManager(const UObject* WorldContextObject);
};
