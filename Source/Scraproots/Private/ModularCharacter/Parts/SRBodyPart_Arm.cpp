// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Arm.h"

void ASRBodyPart_Arm::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the arm-specific preset
	const FSRBodyPartPreset_Arm& ArmPreset = static_cast<const FSRBodyPartPreset_Arm&>(Preset);

	if (ArmPreset.ArmSchemaDataAsset == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart_Arm::InitializeFromPreset: ArmSchemaDataAsset is null"));
		return;
	}

	const FSRBodyPartSchema_Arm& ArmSchema = ArmPreset.ArmSchemaDataAsset->ArmSchema;
	
	if (Preset.BodyPartType == ESRBodyPartType::LeftArm)
	{
		BaseMesh = ArmSchema.MeshLeft;
		AttachmentSocket = ArmSchema.AttachmentSocketLeft;
	}
	else if (Preset.BodyPartType == ESRBodyPartType::RightArm)
	{
		BaseMesh = ArmSchema.MeshRight;
		AttachmentSocket = ArmSchema.AttachmentSocketRight;
	}

	Super::InitializeFromPreset(Preset);
}
