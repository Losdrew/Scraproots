// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SRLevelTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRLevelUtilities.generated.h"

struct FSRLevel;
class USRLevelSubsystem;

UCLASS()
class SCRAPROOTS_API USRLevelUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Opens the level by its data */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static void OpenLevel(UObject const* WorldContextObject, const FSRLevel& Level);

	/** Opens the level by soft reference to the world */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static void OpenLevelByWorld(UObject const* WorldContextObject, TSoftObjectPtr<UWorld> World, TSubclassOf<AGameModeBase> GameMode = nullptr);

	/** Returns index of level in the levels array */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static int32 GetIndexOfLevel(UObject const* WorldContextObject, const FSRLevel& Level);

	/** Returns the current level */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static const FSRLevel& GetCurrentLevel(UObject const* WorldContextObject);

	/** Returns the next level, if available */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static bool TryGetNextLevel(UObject const* WorldContextObject, FSRLevel& OutNextLevel, int32 PartySize);

	/** Returns all levels */
	UFUNCTION(BlueprintCallable, Category = "Levels", meta = (WorldContext = "WorldContextObject"))
	static const TArray<FSRLevel>& GetAllLevels(UObject const* WorldContextObject);

	/** Initializes the shuffled level order (Opening_Level always first) */
	UFUNCTION(BlueprintCallable, Category = "Levels")
	static void InitializeLevelOrder();

	/** Returns the next level of a given size */
	UFUNCTION(BlueprintCallable, Category = "Levels")
	static FSRLevel GetNextLevel(int32 PartySize);

	// Returns the shuffled level order
	UFUNCTION(BlueprintCallable, Category = "Levels")
	static const TArray<FName>& GetShuffledLevels();

	// Returns the current level index
	UFUNCTION(BlueprintCallable, Category = "Levels")
	static int32 GetCurrentLevelIndex();

	// Sets the current level index
	UFUNCTION(BlueprintCallable, Category = "Levels")
	static void SetCurrentLevelIndex(int32 NewIndex);

private:
	/** Helper to get the level subsystem */
	static USRLevelSubsystem* GetLevelSubsystem(UObject const* WorldContextObject);

	/** Array storing shuffled level order */
	static TArray<FName> ShuffledLevels;

	/** Index of the current level */
	static int32 CurrentLevelIndex;
};
