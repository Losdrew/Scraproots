// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Inventory/SRInventoryTypes.h"
#include "SRInventorySettings.generated.h"

USTRUCT(BlueprintType)
struct FSRInventoryConfig
{
	GENERATED_BODY()

	// Initial items to add to the Inventory on initialization
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "BodyPart"))
	FGameplayTagContainer InitialItems;
};

UCLASS(Config = Game, DefaultConfig, DisplayName = "Inventory Settings")
class USRInventorySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

	UPROPERTY(Config, EditAnywhere, Category = "Inventory", meta = (ShowOnlyInnerProperties))
	FSRInventoryConfig InventoryConfig;
};
