// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Torso.h"

#include "Core/SRAssetManager.h"

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
	BaseMesh = TorsoSchema.Mesh;
	AttachmentSocket = TorsoSchema.AttachmentSocket;

	USRAssetManager& AssetManager = USRAssetManager::Get();
	AssetManager.SetSkeletalMeshAsync(BaseMesh, MeshComponent, [this]() 
	{
		OnMeshLoaded();
	});
	MeshComponent->SetAnimInstanceClass(AnimInstanceClass);

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
