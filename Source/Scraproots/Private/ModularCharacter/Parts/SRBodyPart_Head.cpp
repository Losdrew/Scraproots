// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart_Head.h"

#include "Core/SRAssetManager.h"

void ASRBodyPart_Head::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	// Cast the base preset to the head-specific preset
	const FSRBodyPartPreset_Head& HeadPreset = static_cast<const FSRBodyPartPreset_Head&>(Preset);

	if (HeadPreset.HeadSchemaDataAsset == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart_Head::InitializeFromPreset: HeadSchemaDataAsset is null"));
		return;
	}

	const FSRBodyPartSchema_Head& HeadSchema = HeadPreset.HeadSchemaDataAsset->HeadSchema;
	BaseMesh = HeadSchema.Mesh;
	AttachmentSocket = HeadSchema.AttachmentSocket;
	AnimInstanceClass = HeadSchema.AnimInstanceClass;

	USRAssetManager& AssetManager = USRAssetManager::Get();
	AssetManager.SetSkeletalMeshAsync(BaseMesh, MeshComponent, [this]() 
	{
		OnMeshLoaded();
	});

	Super::InitializeFromPreset(Preset);
}

void ASRBodyPart_Head::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, true);
			AttachToComponent(BodyPart->MeshComponent, AttachmentRules, AttachmentSocket);
			FRotator Rotation = BodyPart->GetActorRotation();
			AddActorWorldRotation(FRotator(Rotation));
		}
	}
}