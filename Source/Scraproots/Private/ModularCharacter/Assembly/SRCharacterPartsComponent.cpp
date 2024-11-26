// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Assembly/SRCharacterPartsComponent.h"

#include "Core/SRAssetManager.h"
#include "GameFramework/Character.h"
#include "ModularCharacter/Parts/SRBodyPart.h"
#include "ModularCharacter/SRModularCharacter.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "ModularCharacter/SRModularCharacterUtils.h"

USRCharacterPartsComponent::USRCharacterPartsComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

void USRCharacterPartsComponent::SetBodyPartsFromPreset(const FSRModularCharacterPreset& Preset)
{
	SetBodyPart(Preset.LeftArmPreset);
	SetBodyPart(Preset.RightArmPreset);
	SetBodyPart(Preset.LegsPreset);
	SetBodyPart(Preset.HeadPreset);
	SetBodyPart(Preset.TorsoPreset);
}

void USRCharacterPartsComponent::SetBodyPart(const FSRBodyPartPreset& PartPreset)
{
	USRBodyPartSchemaData* BodyPartSchemaData = USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(this, PartPreset.ProductTag);
	if (BodyPartSchemaData == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::SetBodyPart: Body part schema data is null"));
		return;
	}

	const FSRBodyPartSchema& BodyPartSchema = BodyPartSchemaData->GetBodyPartSchema();
	TSubclassOf<ASRBodyPart> BodyPartClass = BodyPartSchema.GetBodyPartClass();
	if (BodyPartClass == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::SetBodyPart: Body part class is null"));
		return;
	}

	AActor* Owner = GetOwner();
	if (Owner == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("USRCharacterPartsComponent::SetBodyPart: Owner is null"));
		return;
	}

	ASRBodyPart* NewBodyPart = GetWorld()->SpawnActorDeferred<ASRBodyPart>(BodyPartClass, FTransform::Identity, Owner);
	if (NewBodyPart)
	{
		NewBodyPart->InitializeFromPreset(PartPreset);
		if (NewBodyPart->bInitialized)
		{
			NewBodyPart->FinishSpawning(FTransform::Identity);
			RemoveBodyPart(PartPreset.BodyPartType);
			BodyParts.Add(PartPreset.BodyPartType, NewBodyPart);
			OnBodyPartAdded(NewBodyPart);
			AttachBodyParts();
		}
		else
		{
			UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::SetBodyPart: Failed to initialize body part"));
			NewBodyPart->Destroy();
		}
	}
	else
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::SetBodyPart: Failed to spawn body part actor"));
		return;
	}
}

void USRCharacterPartsComponent::OnBodyPartAdded(ASRBodyPart* BodyPart)
{
	OnBodyPartAddedDelegate.Broadcast(BodyPart);
}

void USRCharacterPartsComponent::OnBodyPartRemoved(ASRBodyPart* BodyPart)
{
	OnBodyPartRemovedDelegate.Broadcast(BodyPart);
}

void USRCharacterPartsComponent::RemoveBodyPart(ESRBodyPartType BodyPartType)
{
	if (ASRBodyPart* BodyPart = GetBodyPartByPartType(BodyPartType))
	{
		DetachBodyPart(BodyPart);
		BodyParts.Remove(BodyPartType);
		OnBodyPartRemoved(BodyPart);
		BodyPart->Destroy();
	}
	else
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::RemoveBodyPart: Body part not found"));
	}
}

ASRBodyPart* USRCharacterPartsComponent::GetBodyPartByPartType(ESRBodyPartType PartType) const
{
	if (TObjectPtr<ASRBodyPart> const* BodyPart = BodyParts.Find(PartType))
	{
		return *BodyPart;
	}

	return nullptr;
}

const TMap<ESRBodyPartType, ASRBodyPart*> USRCharacterPartsComponent::GetAllBodyParts() const
{
	 TMap<ESRBodyPartType, ASRBodyPart*> Result;
	 for (const auto& Elem : BodyParts)
	 {
		 Result.Add(Elem.Key, Elem.Value.Get());
	 }
	 return Result;
}

void USRCharacterPartsComponent::AttachBodyParts()
{
	USkeletalMeshComponent* ParentMeshComponent = GetParentMeshComponent();
	if (ParentMeshComponent == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRCharacterPartsComponent::AttachBodyParts: Parent mesh component is null"));
		return;
	}
	
	ASRBodyPart* Legs = GetBodyPartByPartType(ESRBodyPartType::Legs);
	ASRBodyPart* Torso = GetBodyPartByPartType(ESRBodyPartType::Torso);
	ASRBodyPart* Head = GetBodyPartByPartType(ESRBodyPartType::Head);
	ASRBodyPart* LeftArm = GetBodyPartByPartType(ESRBodyPartType::LeftArm);
	ASRBodyPart* RightArm = GetBodyPartByPartType(ESRBodyPartType::RightArm);

	auto AttachOrAdd = [&](ASRBodyPart* Parent, ASRBodyPart* Child) 
	{
		if (Parent)
		{
			Parent->AddAttachmentBodyPart(Child);
		}
		else
		{
			if (Child)
			{
				Child->AttachToComponent(ParentMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}
	};

	if (Legs)
	{
		Legs->AttachToComponent(ParentMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	AttachOrAdd(Legs, Torso);
	AttachOrAdd(Torso, Head);
	AttachOrAdd(Torso, LeftArm);
	AttachOrAdd(Torso, RightArm);
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
