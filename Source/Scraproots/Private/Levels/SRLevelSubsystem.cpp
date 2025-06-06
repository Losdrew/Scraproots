// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelSubsystem.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/SRLevelTypes.h"
#include "Levels/SRLevelSettings.h"
#include "Levels/SRLevelUtilities.h"  // Added to access shuffled levels
#include "Algo/RandomShuffle.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRLevelSubsystem, Log, All);

void USRLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogSRLevelSubsystem, Error, TEXT("LevelSettings not found!"));
		return;
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;

	Levels.Empty();

	for (const auto& Entry : LevelMap)
	{
		Levels.Append(Entry.Value.Levels);
	}

	USRLevelUtilities::InitializeLevelOrder();

	UE_LOG(LogSRLevelSubsystem, Log, TEXT("SRLevelSubsystem initialized with %d levels"), Levels.Num());
}

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
			{ return Level.LevelWorld.GetAssetName() == World->GetName(); });

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

bool USRLevelSubsystem::TryGetNextLevel(FSRLevel& OutNextLevel, int32 PartySize)
{
	if (USRLevelUtilities::GetCurrentLevelIndex() >= 5)
	{
		UE_LOG(LogSRLevelSubsystem, Warning, TEXT("All levels have been played."));
		return false;
	}

	FName NextLevelName = USRLevelUtilities::GetShuffledLevels()[USRLevelUtilities::GetCurrentLevelIndex()];

	int32 NewIndex = USRLevelUtilities::GetCurrentLevelIndex() + 1;
	USRLevelUtilities::SetCurrentLevelIndex(NewIndex);

	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogSRLevelSubsystem, Error, TEXT("Failed to load LevelSettings!"));
		return false;
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;
	const FSRLevelList* LevelList = LevelMap.Find(NextLevelName);

	if (!LevelList || LevelList->Levels.Num() == 0)
	{
		UE_LOG(LogSRLevelSubsystem, Warning, TEXT("No levels found for: %s"), *NextLevelName.ToString());
		return false;
	}

	ESRLevelSize RequiredSize;
	switch (PartySize)
	{
		case 1: RequiredSize = ESRLevelSize::Small; break;
		case 2: RequiredSize = ESRLevelSize::Medium; break;
		case 3:
		default: RequiredSize = ESRLevelSize::Big; break;
	}

	for (const FSRLevel& Level : LevelList->Levels)
	{
		if (Level.LevelSize == RequiredSize)
		{
			OutNextLevel = Level;
			UE_LOG(LogSRLevelSubsystem, Log, TEXT("Next Level: %s (Size: %d)"), *NextLevelName.ToString(), static_cast<int32>(RequiredSize));
			return true;
		}
	}

	OutNextLevel = LevelList->Levels[0];
	return true;
}

void USRLevelSubsystem::ResetLevelSubsystem()
{
	const USRLevelSettings* LevelSettings = GetDefault<USRLevelSettings>();
	if (!LevelSettings)
	{
		UE_LOG(LogSRLevelSubsystem, Error, TEXT("LevelSettings not found!"));
		return;
	}

	const TMap<FName, FSRLevelList>& LevelMap = LevelSettings->LevelConfig;

	Levels.Empty();

	for (const auto& Entry : LevelMap)
	{
		Levels.Append(Entry.Value.Levels);
	}

	USRLevelUtilities::InitializeLevelOrder();

	UE_LOG(LogSRLevelSubsystem, Log, TEXT("SRLevelSubsystem has been reset."));
}