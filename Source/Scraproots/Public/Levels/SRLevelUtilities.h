// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRLevelUtilities.generated.h"

struct FSRLevel;
class USRLevelSubsystem;

UCLASS()
class SCRAPROOTS_API USRLevelUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Opens the level by its data
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static void OpenLevel(UObject const* WorldContextObject, const FSRLevel& Level);

	// Opens the level by soft reference to the world
	// @param	GameMode	Can be left empty. Used to open the level with a game mode other than the default one
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static void OpenLevelByWorld(UObject const* WorldContextObject, TSoftObjectPtr<UWorld> World, TSubclassOf<AGameModeBase> GameMode = nullptr);

	// Returns index of level in the levels array
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static int32 GetIndexOfLevel(UObject const* WorldContextObject, const FSRLevel& Level);

	// Returns the current level
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static const FSRLevel& GetCurrentLevel(UObject const* WorldContextObject);

	// Returns the level that comes after the current one
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static bool TryGetNextLevel(UObject const* WorldContextObject, FSRLevel& OutNextLevel);

	// Returns an array of all levels
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static const TArray<FSRLevel>& GetAllLevels(UObject const* WorldContextObject);

private:
	static USRLevelSubsystem* GetLevelSubsystem(UObject const* WorldContextObject);
};
