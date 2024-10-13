// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Torso.h"

void ASRBodyPart_Torso::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the torso-specific preset
	const FSRBodyPartPreset_Torso& TorsoPreset = static_cast<const FSRBodyPartPreset_Torso&>(Preset);

	if (TorsoPreset.TorsoSchemaDataAsset == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart_Torso::InitializeFromPreset: TorsoSchemaDataAsset is null"));
		return;
	}

	const FSRBodyPartSchema_Torso& TorsoSchema = TorsoPreset.TorsoSchemaDataAsset->TorsoSchema;

	// Set base mesh to first cosmetic mesh by default
	BaseMesh = TorsoSchema.Mesh;

	Super::InitializeFromPreset(Preset);
}
