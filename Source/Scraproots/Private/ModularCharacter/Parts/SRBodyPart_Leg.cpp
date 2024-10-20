// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Leg.h"

#include "Core/SRAssetManager.h"

void ASRBodyPart_Leg::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the leg-specific preset
	const FSRBodyPartPreset_Leg& LegPreset = static_cast<const FSRBodyPartPreset_Leg&>(Preset);

	if (LegPreset.LegSchemaDataAsset == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart_Leg::InitializeFromPreset: LegSchemaDataAsset is null"));
		return;
	}

	const FSRBodyPartSchema_Leg& LegSchema = LegPreset.LegSchemaDataAsset->LegSchema;
	BaseMesh = LegSchema.Mesh;
	AttachmentSocket = LegSchema.AttachmentSocket;

	USRAssetManager& AssetManager = USRAssetManager::Get();
	AssetManager.SetSkeletalMeshAsync(BaseMesh, MeshComponent, [this]() 
	{
		OnMeshLoaded();
	});
	MeshComponent->SetAnimInstanceClass(AnimInstanceClass);

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Leg::AttachToBodyPart(ASRBodyPart* BodyPart)
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
