// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "Product/SRProductTypes.h"
#include "SRDeveloperSettings.generated.h"

UCLASS(config = Game, defaultconfig, MinimalAPI)
class USRDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	USRDeveloperSettings();

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

	//~UObject interface
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;
	virtual void PostInitProperties() override;
#endif
	//~End of UObject interface

public:
	UPROPERTY(config, EditAnywhere, Category = "Modular Character")
	FSRModularCharacterConfig ModularCharacterConfig;

	UPROPERTY(config, EditAnywhere, Category = "Products")
	FSRProductsConfig ProductsConfig;
};