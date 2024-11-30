// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelSubsystem.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/SRLevelTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRLevelSubsystem, Log, All);

void USRLevelSubsystem::SetLevels(const TArray<FSRLevel>& InLevels)
{
	Levels = InLevels;
}

void USRLevelSubsystem::OpenLevel(const FSRLevel& Level)
{
	CurrentLevel = Level;
	OpenLevel_Internal(Level.LevelWorld, Level.GameMode);
}

void USRLevelSubsystem::OpenLevelByWorld(TSoftObjectPtr<UWorld> World, TSubclassOf<AGameModeBase> GameMode)
{
	OpenLevel_Internal(World, GameMode);
}

void USRLevelSubsystem::OpenLevel_Internal(TSoftObjectPtr<UWorld> LevelWorld, TSubclassOf<AGameModeBase> GameMode)
{
	FString Options;
	if (GameMode != nullptr)
	{
		Options = FString::Printf(TEXT("?game=%s"), *GameMode->GetPathName());
	}

	UGameplayStatics::OpenLevelBySoftObjectPtr(GetGameInstance(), LevelWorld, true, Options);
}

const FSRLevel& USRLevelSubsystem::GetCurrentLevel()
{
	// If current level is empty, try to find it in the levels array
	if (!CurrentLevel.IsValid())
	{
		const UWorld* World = GetWorld();
		if (World == nullptr)
		{
			return CurrentLevel;
		}

		FSRLevel* FoundLevel = Levels.FindByPredicate([World](const FSRLevel& Level)
		{ 
			return Level.LevelWorld.GetAssetName() == World->GetName(); 
		});

		if (FoundLevel != nullptr)
		{
			CurrentLevel = *FoundLevel;
		}
		else
		{
			UE_LOG(LogSRLevelSubsystem, Error, TEXT("Current level not found in levels array"));
		}
	}

	return CurrentLevel;
}

bool USRLevelSubsystem::TryGetNextLevel(FSRLevel& OutNextLevel) const
{
	int32 CurrentLevelIndex = GetIndexOfLevel(CurrentLevel);
	if (CurrentLevelIndex == INDEX_NONE || !Levels.IsValidIndex(CurrentLevelIndex + 1))
	{
		UE_LOG(LogSRLevelSubsystem, Error, TEXT("Can't open next level: current level is invalid or there is no next level."));
		return false;
	}
	OutNextLevel = Levels[CurrentLevelIndex + 1];
	return true;
}
