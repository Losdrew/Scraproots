// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Assembly/SRCharacterPartsComponent.h"

#include "Core/SRAssetManager.h"
#include "GameFramework/Character.h"
#include "ModularCharacter/Parts/SRBodyPart.h"
#include "ModularCharacter/SRModularCharacterTypes.h"

USRCharacterPartsComponent::USRCharacterPartsComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

void USRCharacterPartsComponent::Initialize(TArray<TObjectPtr<ASRBodyPart>>* BodyParts)
{
	BodyPartsPtr = BodyParts;
}

void USRCharacterPartsComponent::AddBodyPart(const FSRBodyPartPreset& PartPreset)
{
	if (BodyPartsPtr == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AddBodyPart: Body parts array is null"));
		return;
	}

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
			BodyPartsPtr->Add(NewBodyPart);
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
	if (BodyPartsPtr == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::RemoveBodyPart: Body part array is null"));
		return;
	}

	if (ASRBodyPart* BodyPart = GetBodyPartByPartType(BodyPartType))
	{
		if (BodyPart)
		{
			DetachBodyPart(BodyPart);
			BodyPartsPtr->Remove(BodyPart);
		}
	}
	else
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::RemoveBodyPart: Body part not found"));
	}
}

ASRBodyPart* USRCharacterPartsComponent::GetBodyPartByPartType(ESRBodyPartType PartType) const
{
	if (BodyPartsPtr == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::GetBodyPartByPartType: Body part array is null"));
		return nullptr;
	}

	if (!BodyPartsPtr->IsEmpty())
	{
		for (ASRBodyPart* BodyPart : *BodyPartsPtr)
		{
			if (BodyPart->BodyPartType == PartType)
			{
				return BodyPart;
			}
		}
	}

	return nullptr;
}

TArray<ASRBodyPart*> USRCharacterPartsComponent::GetAllBodyParts() const
{
	if (BodyPartsPtr != nullptr)
	{
		return *BodyPartsPtr;
	}

	UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::GetAllBodyParts: Body part array is null"));
	return TArray<ASRBodyPart*>();
}

void USRCharacterPartsComponent::AttachBodyParts()
{
	if (BodyPartsPtr == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AttachBodyParts: Body part array is null"));
		return;
	}

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

	for (ASRBodyPart* BodyPart : *BodyPartsPtr)
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
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwnerActor))
		{
			if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
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
