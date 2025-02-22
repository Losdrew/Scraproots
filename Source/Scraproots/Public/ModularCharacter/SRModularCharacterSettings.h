// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "SRModularCharacterSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, DisplayName = "Modular Character Settings")
class USRModularCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

public:
	UPROPERTY(Config, EditAnywhere, Category = "Modular Character", meta = (ShowOnlyInnerProperties))
	FSRModularCharacterConfig ModularCharacterConfig;
};