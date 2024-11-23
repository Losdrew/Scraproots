// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Torso.h"

#include "ModularCharacter/SRModularCharacterUtils.h"

void ASRBodyPart_Torso::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the torso-specific preset
	const FSRBodyPartPreset_Torso& TorsoPreset = static_cast<const FSRBodyPartPreset_Torso&>(Preset);

	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, Preset.ProductTag);
	USRTorsoSchemaData* TorsoSchemaData = Cast<USRTorsoSchemaData>(BodyPartSchemaData);
	if (TorsoSchemaData == nullptr)
	{
		return;
	}

	const FSRBodyPartSchema_Torso& TorsoSchema = TorsoSchemaData->TorsoSchema;
	BaseMesh = TorsoSchema.Mesh;
	AttachmentSocket = TorsoSchema.AttachmentSocket;

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Torso::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->BodyPartType == ESRBodyPartType::Legs && BodyPart->MeshComponent)
		{
			AttachToLegs(BodyPart);
		}
	}
}
