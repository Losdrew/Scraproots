// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Torso.h"

#include "ModularCharacter/SRModularCharacterSettings.h"
#include "ModularCharacter/SRModularCharacterUtils.h"

FSRBodyPartSchema_Torso::FSRBodyPartSchema_Torso()
	: Super()
{
	const USRModularCharacterSettings* ModularCharacterSettings = GetDefault<USRModularCharacterSettings>();
	TorsoClass = ModularCharacterSettings->ModularCharacterConfig.DefaultTorsoClass;
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
	NoLegsOffset = TorsoSchema.NoLegsOffset;

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Torso::AttachToMeshComponent(USkeletalMeshComponent* InMeshComponent)
{
	if (InMeshComponent)
	{
		AttachToComponent(InMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		MeshComponent->SetRelativeLocation(FVector::ZeroVector);
		MeshComponent->AddLocalOffset(NoLegsOffset);
	}
}

void ASRBodyPart_Torso::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart && BodyPart->MeshComponent && BodyPart->BodyPartType == ESRBodyPartType::Legs)
	{
		MeshComponent->SetRelativeLocation(FVector::ZeroVector);
		AttachToLegs(BodyPart);
		MeshComponent->AddWorldOffset(LegsOffset);
	}
}
