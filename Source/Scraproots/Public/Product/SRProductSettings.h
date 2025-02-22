// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Product/SRProductTypes.h"
#include "SRProductSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, DisplayName = "Product Settings")
class USRProductSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

public:
	UPROPERTY(Config, EditAnywhere, Category = "Products", meta = (ShowOnlyInnerProperties))
	FSRProductsConfig ProductsConfig;
};