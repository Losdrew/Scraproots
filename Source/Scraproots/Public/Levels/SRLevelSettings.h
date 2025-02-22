// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Levels/SRLevelTypes.h"
#include "SRLevelSettings.generated.h"

USTRUCT(BlueprintType)
struct FSRLevelConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSRLevel> Levels;
};

UCLASS(Config = Game, DefaultConfig, DisplayName = "Level Settings")
class USRLevelSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Level", meta = (ShowOnlyInnerProperties))
	FSRLevelConfig LevelConfig;
};
