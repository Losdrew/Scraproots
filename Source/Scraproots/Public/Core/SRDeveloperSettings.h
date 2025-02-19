// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "Product/SRProductTypes.h"
#include "SRDeveloperSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, DisplayName = "Developer Settings")
class USRDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

public:
	UPROPERTY(config, EditAnywhere, Category = "Modular Character")
	FSRModularCharacterConfig ModularCharacterConfig;

	UPROPERTY(config, EditAnywhere, Category = "Products")
	FSRProductsConfig ProductsConfig;
};