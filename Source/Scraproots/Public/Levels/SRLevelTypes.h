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
	ESRLevelType LevelType;
};
