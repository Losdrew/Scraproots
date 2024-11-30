// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Head.h"

#include "ModularCharacter/SRModularCharacterUtils.h"

void ASRBodyPart_Head::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, Preset.ProductTag);
	USRHeadSchemaData* HeadSchemaData = Cast<USRHeadSchemaData>(BodyPartSchemaData);
	if (HeadSchemaData == nullptr)
	{
		return;
	}

	const FSRBodyPartSchema_Head& HeadSchema = HeadSchemaData->HeadSchema;
	BaseMesh = HeadSchema.Mesh;
	AttachmentSocket = HeadSchema.AttachmentSocket;
	AnimInstanceClass = HeadSchema.AnimInstanceClass;

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Head::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			AttachToComponent(BodyPart->MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachmentSocket);
		}
	}
}