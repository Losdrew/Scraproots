// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Assembly/SRCharacterPartsComponent.h"

#include "Core/SRAssetManager.h"
#include "GameFramework/Character.h"
#include "ModularCharacter/Parts/SRBodyPart.h"
#include "ModularCharacter/SRModularCharacter.h"
#include "ModularCharacter/SRModularCharacterTypes.h"

USRCharacterPartsComponent::USRCharacterPartsComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

void USRCharacterPartsComponent::AddBodyPartsFromPreset(const FSRModularCharacterPreset& Preset)
{
	AddBodyPart(Preset.LeftArmPreset);
	AddBodyPart(Preset.RightArmPreset);
	AddBodyPart(Preset.LegsPreset);
	AddBodyPart(Preset.HeadPreset);
	AddBodyPart(Preset.TorsoPreset);

	AttachBodyParts();
}

void USRCharacterPartsComponent::AddBodyPart(const FSRBodyPartPreset& PartPreset)
{
	// Not adding body part of this type if it already exists in the character
	if (GetBodyPartByPartType(PartPreset.BodyPartType))
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Body part already exists in the character"));
		return;
	}

	USRBodyPartSchemaData* BodyPartSchemaData = PartPreset.GetBodyPartSchemaData();
	if (BodyPartSchemaData == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Body part schema data is null"));
		return;
	}

	const FSRBodyPartSchema& BodyPartSchema = BodyPartSchemaData->GetBodyPartSchema();
	TSubclassOf<ASRBodyPart> BodyPartClass = BodyPartSchema.GetBodyPartClass();
	if (BodyPartClass == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Body part class is null"));
		return;
	}

	AActor* Owner = GetOwner();
	if (Owner == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("USRCharacterPartsComponent::AddBodyPart: Owner is null"));
		return;
	}

	ASRBodyPart* NewBodyPart = GetWorld()->SpawnActorDeferred<ASRBodyPart>(BodyPartClass, FTransform::Identity, Owner);
	if (NewBodyPart)
	{
		NewBodyPart->InitializeFromPreset(PartPreset);
		if (NewBodyPart->bInitialized)
		{
			NewBodyPart->FinishSpawning(FTransform::Identity);
			BodyParts.Add(NewBodyPart);
		}
		else
		{
			UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Failed to initialize body part"));
			NewBodyPart->Destroy();
		}
	}
	else
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Failed to spawn body part actor"));
		return;
	}
}

void USRCharacterPartsComponent::RemoveBodyPart(ESRBodyPartType BodyPartType)
{
	if (ASRBodyPart* BodyPart = GetBodyPartByPartType(BodyPartType))
	{
		if (BodyPart)
		{
			DetachBodyPart(BodyPart);
			BodyParts.Remove(BodyPart);
		}
	}
	else
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::RemoveBodyPart: Body part not found"));
	}
}

ASRBodyPart* USRCharacterPartsComponent::GetBodyPartByPartType(ESRBodyPartType PartType) const
{
	for (ASRBodyPart* BodyPart : BodyParts)
	{
		if (BodyPart->BodyPartType == PartType)
		{
			return BodyPart;
		}
	}

	return nullptr;
}

TArray<ASRBodyPart*> USRCharacterPartsComponent::GetAllBodyParts() const
{
	return BodyParts;
}

void USRCharacterPartsComponent::AttachBodyParts()
{
	ASRBodyPart* Torso = GetBodyPartByPartType(ESRBodyPartType::Torso);
	if (Torso == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AttachBodyParts: Torso not found"));
		return;
	}

	USkeletalMeshComponent* ParentMeshComponent = GetParentMeshComponent();
	if (ParentMeshComponent == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AttachBodyParts: Parent mesh component is null"));
		return;
	}

	Torso->AttachToComponent(ParentMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	for (ASRBodyPart* BodyPart : BodyParts)
	{
		if (BodyPart == Torso)
		{
			continue;
		}

		// The torso should attach to the legs if there are any
		if (BodyPart->BodyPartType == ESRBodyPartType::Legs)
		{
			BodyPart->AttachToComponent(ParentMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
			BodyPart->AddAttachmentBodyPart(Torso);
		}
		else
		{
			Torso->AddAttachmentBodyPart(BodyPart);
		}
	}
}

USkeletalMeshComponent* USRCharacterPartsComponent::GetParentMeshComponent() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		// If the parent actor is derived from ACharacter, returns the character mesh
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwnerActor))
		{
			if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
			{
				return MeshComponent;
			}
		}
		// If the parent actor is derived from AActor, search for a skeletal mesh component
		else if (AActor* OwningActor = Cast<AActor>(OwnerActor))
		{
			if (USkeletalMeshComponent* MeshComponent = OwningActor->FindComponentByClass<USkeletalMeshComponent>())
			{
				return MeshComponent;
			}
		}
	}

	return nullptr;
}

void USRCharacterPartsComponent::DetachBodyPart(ASRBodyPart* BodyPart)
{
	BodyPart->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}
