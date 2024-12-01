// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Arm.h"

#include "Core/SRDeveloperSettings.h"
#include "ModularCharacter/SRModularCharacterUtils.h"

FSRBodyPartSchema_Arm::FSRBodyPartSchema_Arm()
	: Super()
{
	const USRDeveloperSettings* DeveloperSettings = GetDefault<USRDeveloperSettings>();
	ArmClass = DeveloperSettings->ModularCharacterConfig.DefaultArmClass;
}

//////////////////////////////////////////////////

void ASRBodyPart_Arm::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, Preset.ProductTag);
	USRArmSchemaData* ArmSchemaData = Cast<USRArmSchemaData>(BodyPartSchemaData);
	if (ArmSchemaData == nullptr)
	{
		return;
	}

	const FSRBodyPartSchema_Arm& ArmSchema = ArmSchemaData->ArmSchema;
	
	if (Preset.BodyPartType == ESRBodyPartType::LeftArm)
	{
		BaseMesh = ArmSchema.MeshLeft;
		AttachmentSocket = ArmSchema.AttachmentSocketLeft;
		AnimInstanceClass = ArmSchema.AnimInstanceClassLeft;
	}
	else if (Preset.BodyPartType == ESRBodyPartType::RightArm)
	{
		BaseMesh = ArmSchema.MeshRight;
		AttachmentSocket = ArmSchema.AttachmentSocketRight;
		AnimInstanceClass = ArmSchema.AnimInstanceClassRight;
	}

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Arm::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			AttachToComponent(BodyPart->MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachmentSocket);
		}
	}
}

