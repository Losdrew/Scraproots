// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Torso.h"

#include "Core/SRDeveloperSettings.h"
#include "ModularCharacter/SRModularCharacterUtils.h"

FSRBodyPartSchema_Torso::FSRBodyPartSchema_Torso()
	: Super()
{
	const USRDeveloperSettings* DeveloperSettings = GetDefault<USRDeveloperSettings>();
	TorsoClass = DeveloperSettings->ModularCharacterConfig.DefaultTorsoClass;
}

//////////////////////////////////////////////////

void ASRBodyPart_Torso::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, Preset.ProductTag);
	USRTorsoSchemaData* TorsoSchemaData = Cast<USRTorsoSchemaData>(BodyPartSchemaData);
	if (TorsoSchemaData == nullptr)
	{
		return;
	}

	const FSRBodyPartSchema_Torso& TorsoSchema = TorsoSchemaData->TorsoSchema;
	BaseMesh = TorsoSchema.Mesh;
	AttachmentSocket = TorsoSchema.AttachmentSocket;
	AnimInstanceClass = TorsoSchema.AnimInstanceClass;

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
