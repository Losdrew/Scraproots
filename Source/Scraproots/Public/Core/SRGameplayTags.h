// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "SRGameplayTags.generated.h"

/**
 *  Centralized location for all gameplay tags used in C++ code.
 */
USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRTag_Event
{
	GENERATED_BODY()

	static const FGameplayTag Inventory_ItemsChanged;
};
