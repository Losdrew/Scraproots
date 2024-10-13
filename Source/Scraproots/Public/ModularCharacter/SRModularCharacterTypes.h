// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SRModularCharacterTypes.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRModularCharacter, Log, All);

UENUM(BlueprintType)
enum class ESRBodyPartType : uint8
{
	None,
	Head,
	Torso,
	LeftArm,
	RightArm,
	Legs,
	Spine
};

UENUM(BlueprintType)
enum class ESRRarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary
};
