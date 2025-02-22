// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Leg.h"

#include "ModularCharacter/SRModularCharacterSettings.h"
#include "ModularCharacter/SRModularCharacterUtils.h"

FSRBodyPartSchema_Leg::FSRBodyPartSchema_Leg()
	: Super()
{
	const USRModularCharacterSettings* ModularCharacterSettings = GetDefault<USRModularCharacterSettings>();
	LegClass = ModularCharacterSettings->ModularCharacterConfig.DefaultLegClass;
}

//////////////////////////////////////////////////

void ASRBodyPart_Leg::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
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
