// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Leg.h"

#include "ModularCharacter/SRModularCharacterUtils.h"

void ASRBodyPart_Leg::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the leg-specific preset
	const FSRBodyPartPreset_Leg& LegPreset = static_cast<const FSRBodyPartPreset_Leg&>(Preset);

	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, Preset.ProductTag);
	USRLegSchemaData* LegSchemaData = Cast<USRLegSchemaData>(BodyPartSchemaData);
	if (LegSchemaData == nullptr)
	{
		return;
	}

	const FSRBodyPartSchema_Leg& LegSchema = LegSchemaData->LegSchema;
	BaseMesh = LegSchema.Mesh;
	AttachmentSocket = LegSchema.AttachmentSocket;
	AnimInstanceClass = LegSchema.AnimInstanceClass;

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Leg::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			AttachToComponent(BodyPart->MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachmentSocket);
		}
	}
}
