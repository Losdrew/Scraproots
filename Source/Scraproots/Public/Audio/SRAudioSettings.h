// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "SRAudioSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Audio Settings"))
class SCRAPROOTS_API USRAudioSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	bool bMusicEnabled = true;
};