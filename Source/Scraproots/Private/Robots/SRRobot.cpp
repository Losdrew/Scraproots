// Fill out your copyright notice in the Description page of Project Settings.

#include "Robots/SRRobot.h"

ASRRobot::ASRRobot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
}

void ASRRobot::InitializeFromPreset(const FSRModularCharacterPreset& Preset)
{
	const FSRRobotPreset& RobotPreset = static_cast<const FSRRobotPreset&>(Preset);
	Super::InitializeFromPreset(Preset);
}

void ASRRobot::BeginPlay()
{
	if (RobotDataAsset)
	{
		InitializeFromPreset(RobotDataAsset->CharacterPreset);
	}

	Super::BeginPlay();
}
