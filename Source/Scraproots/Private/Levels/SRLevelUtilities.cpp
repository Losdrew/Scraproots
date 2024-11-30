// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelUtilities.h"

#include "Levels/SRLevelSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USRLevelUtilities::OpenLevel(UObject const* WorldContextObject, const FSRLevel& Level)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		return;
	}
	LevelSubsystem->OpenLevel(Level);
}

void USRLevelUtilities::OpenLevelByWorld(UObject const* WorldContextObject, TSoftObjectPtr<UWorld> World, TSubclassOf<AGameModeBase> GameMode)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		return;
	}
	LevelSubsystem->OpenLevelByWorld(World, GameMode);
}

int32 USRLevelUtilities::GetIndexOfLevel(UObject const* WorldContextObject, const FSRLevel& Level)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		return INDEX_NONE;
	}
	return LevelSubsystem->GetIndexOfLevel(Level);
}

const FSRLevel& USRLevelUtilities::GetCurrentLevel(UObject const* WorldContextObject)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		static FSRLevel EmptyLevel;
		return EmptyLevel;
	}
	return LevelSubsystem->GetCurrentLevel();
}

bool USRLevelUtilities::TryGetNextLevel(UObject const* WorldContextObject, FSRLevel& OutNextLevel)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		return false;
	}
	return LevelSubsystem->TryGetNextLevel(OutNextLevel);
}

const TArray<FSRLevel>& USRLevelUtilities::GetAllLevels(UObject const* WorldContextObject)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		static TArray<FSRLevel> EmptyArray;
		return EmptyArray;
	}
	return LevelSubsystem->GetAllLevels();
}

USRLevelSubsystem* USRLevelUtilities::GetLevelSubsystem(UObject const* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (GameInstance == nullptr)
	{
		return nullptr;
	}
	USRLevelSubsystem* LevelSubsystem = GameInstance->GetSubsystem<USRLevelSubsystem>();
	return LevelSubsystem;
}
