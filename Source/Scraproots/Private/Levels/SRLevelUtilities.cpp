// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelUtilities.h"

#include "Levels/SRLevelSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/SRLevelSettings.h"
#include "Algo/RandomShuffle.h"
#include "Algo/Find.h"

TArray<FName> USRLevelUtilities::ShuffledLevels;
int32 USRLevelUtilities::CurrentLevelIndex = 0;

const TArray<FName>& USRLevelUtilities::GetShuffledLevels()
{
	return ShuffledLevels;
}

int32 USRLevelUtilities::GetCurrentLevelIndex()
{
	return CurrentLevelIndex;
}

void USRLevelUtilities::SetCurrentLevelIndex(int32 NewIndex)
{
	CurrentLevelIndex = NewIndex;
}

void USRLevelUtilities::InitializeLevelOrder()
{
	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load LevelSettings!"));
		return;
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;

	ShuffledLevels.Empty();
	ShuffledLevels.Add("Opening_Level");

	TArray<FName> TempLevels;
	for (const auto& Entry : LevelMap)
	{
		if (Entry.Key != "Opening_Level")
		{
			TempLevels.Add(Entry.Key);
		}
	}

	Algo::RandomShuffle(TempLevels);
	ShuffledLevels.Append(TempLevels);

	CurrentLevelIndex = 0;

	UE_LOG(LogTemp, Log, TEXT("Shuffled Levels Order:"));
	for (const FName& LevelName : ShuffledLevels)
	{
		UE_LOG(LogTemp, Log, TEXT("  - %s"), *LevelName.ToString());
	}
}

FSRLevel USRLevelUtilities::GetNextLevel(int32 PartySize)
{
	if (CurrentLevelIndex >= 5)	 
	{
		UE_LOG(LogTemp, Warning, TEXT("No more levels available!"));
		return FSRLevel();	
	}

	CurrentLevelIndex++;
	FName NextLevelName = ShuffledLevels[CurrentLevelIndex];

	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load LevelSettings!"));
		return FSRLevel();
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;
	const FSRLevelList* LevelList = LevelMap.Find(NextLevelName);

	ESRLevelSize RequiredSize;
	switch (PartySize)
	{
		case 1:
			RequiredSize = ESRLevelSize::Small;
			break;
		case 2:
			RequiredSize = ESRLevelSize::Medium;
			break;
		case 3:
		default:
			RequiredSize = ESRLevelSize::Big;
			break;
	}

	for (const FSRLevel& Level : LevelList->Levels)
	{
		if (Level.LevelSize == RequiredSize)
		{
			UE_LOG(LogTemp, Log, TEXT("Selected Level: %s (Size: %d)"), *NextLevelName.ToString(), static_cast<int32>(RequiredSize));
			return Level;
		}
	}

	// If no exact match, return the first available level
	UE_LOG(LogTemp, Warning, TEXT("No matching level size found, using first available level."));
	return LevelList->Levels[0];
}

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

bool USRLevelUtilities::TryGetNextLevel(UObject const* WorldContextObject, FSRLevel& OutNextLevel, int32 PartySize)
{
	USRLevelSubsystem* LevelSubsystem = GetLevelSubsystem(WorldContextObject);
	if (LevelSubsystem == nullptr)
	{
		return false;
	}
	return LevelSubsystem->TryGetNextLevel(OutNextLevel, PartySize);
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
