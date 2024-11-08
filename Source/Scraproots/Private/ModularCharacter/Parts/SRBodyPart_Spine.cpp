// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Spine.h"

#include "Core/SRAssetManager.h"

void ASRBodyPart_Spine::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the spine-specific preset
	const FSRBodyPartPreset_Spine& SpinePreset = static_cast<const FSRBodyPartPreset_Spine&>(Preset);

	if (SpinePreset.SpineSchemaDataAsset == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart_Spine::InitializeFromPreset: SpineSchemaDataAsset is null"));
		return;
	}

	const FSRBodyPartSchema_Spine& SpineSchema = SpinePreset.SpineSchemaDataAsset->SpineSchema;
	BaseMesh = SpineSchema.Mesh;
	AttachmentSocket = SpineSchema.AttachmentSocket;
	AnimInstanceClass = SpineSchema.AnimInstanceClass;

	USRAssetManager& AssetManager = USRAssetManager::Get();
	AssetManager.SetSkeletalMeshAsync(BaseMesh, MeshComponent, [this]() 
	{
		OnMeshLoaded();
	});

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Spine::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, true);
			AttachToComponent(BodyPart->MeshComponent, AttachmentRules, AttachmentSocket);
		}
	}
}
