// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SRLevelTypes.generated.h"

UENUM(BlueprintType)
enum class ESRLevelType : uint8
{
	Opening		UMETA(ToolTip = "Level at the start of the run (no combat)."),
	Battle		UMETA(ToolTip = "Level with enemies."),
	Shop		UMETA(ToolTip = "Level with a shop."),
	Boss		UMETA(ToolTip = "Level with a boss fight."),
};

UENUM(BlueprintType)
enum class ESRLevelSize : uint8
{
	Small UMETA(ToolTip = "One unit in party, 7x7 grid"),
	Medium UMETA(ToolTip = "Two units in party, 8x8 grid"),
	Big UMETA(ToolTip = "Three units in party, 10x10 grid"),
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRLevel
{
	GENERATED_BODY()

public:
	FSRLevel()
	{
		Id = Id.IsValid() ? Id : FGuid::NewGuid();
	}

	bool operator==(const FSRLevel& Other) const
	{
		return Id == Other.Id;
	}

	bool IsValid() const
	{
		return Id.IsValid() && !LevelWorld.IsNull();
	}

public:
	// This level's global identifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	FGuid Id;

	// The actual level (map) to load
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TSoftObjectPtr<UWorld> LevelWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TSubclassOf<AGameModeBase> GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	ESRLevelSize LevelSize;
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRLevelList
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TArray<FSRLevel> Levels;
};