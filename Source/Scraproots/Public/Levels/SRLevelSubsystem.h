// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Levels/SRLevelTypes.h"
#include "SRLevelSubsystem.generated.h"

class USRGameInstanceBase;
class AGameModeBase;

UCLASS()
class SCRAPROOTS_API USRLevelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	void SetLevels(const TArray<FSRLevel>& InLevels);

	// Opens the level by its data
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void OpenLevel(const FSRLevel& Level);

	// Opens the level by soft reference to the world
	// @param	GameMode	Can be left empty. Used to open the level with a game mode other than the default one
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void OpenLevelByWorld(TSoftObjectPtr<UWorld> World, TSubclassOf<AGameModeBase> GameMode = nullptr);

	// Returns an array of all levels
	UFUNCTION(BlueprintCallable, Category = "Levels")
	const TArray<FSRLevel>& GetAllLevels() const { return Levels; }

	// Returns index of level in the levels array
	UFUNCTION(BlueprintCallable, Category = "Levels")
	int32 GetIndexOfLevel(const FSRLevel& Level) const { return Levels.IndexOfByKey(Level); };

	// Returns the current level
	UFUNCTION(BlueprintCallable, Category = "Levels")
	const FSRLevel& GetCurrentLevel();

	// Returns the level that comes after the current one
	UFUNCTION(BlueprintCallable, Category = "Levels")
	bool TryGetNextLevel(FSRLevel& OutNextLevel, int32 PartySize);

	UFUNCTION(BlueprintCallable, Category = "Levels")
	int32 GetLevelsNum() const { return Levels.Num(); }

protected:
	void OpenLevel_Internal(TSoftObjectPtr<UWorld> LevelWorld, TSubclassOf<AGameModeBase> GameMode);

protected:
	// Temporary storage for levels
	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	TArray<FSRLevel> Levels;

	UPROPERTY(BlueprintReadOnly, Category = "Levels")
	FSRLevel CurrentLevel;
};
