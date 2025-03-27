// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "SRLevelTypes.h"
#include "SRLevelSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Level Settings"))
class SCRAPROOTS_API USRLevelSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

	// Map of level names to their respective level lists
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Levels")
	TMap<FName, FSRLevelList> LevelConfig;
};