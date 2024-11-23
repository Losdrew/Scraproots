// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart.h"

#include "ModularCharacter/SRModularCharacterTypes.h"
#include "ModularCharacter/SRModularCharacterUtils.h"
#include "Product/SRProductTypes.h"
#include "Core/SRAssetManager.h"

TSubclassOf<ASRBodyPart> FSRBodyPartSchema::GetBodyPartClass() const
{
	return ASRBodyPart::StaticClass();
}

//////////////////////////////////////////////////

ASRBodyPart::ASRBodyPart()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	SetBodyPartMeshParameters(MeshComponent);
}

void ASRBodyPart::InitializeFromPreset(const FSRBodyPartPreset& Preset)
{
	FSRProductDefinition* ProductDef = USRModularCharacterUtils::GetProductDefinitionByProductTag(this, Preset.ProductTag);
	if (!ProductDef)
	{
		return;
	}

	USRBodyPartSchemaData* SchemaData = Cast<USRBodyPartSchemaData>(ProductDef->Schema);
	if (!SchemaData)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart::InitializeFromPreset: Body Part Schema Data not found for %s"), *Preset.ProductTag.ToString());
		return;	
	}

	const FSRBodyPartSchema& BodyPartSchema = SchemaData->GetBodyPartSchema();
	BodyPartType = Preset.BodyPartType;
	ProductTag = Preset.ProductTag;

	const FSRItemDetails& ItemDetails = ProductDef->ItemDetails;
	Stats = ItemDetails.Stats;
	Abilities = ItemDetails.Abilities;
	Weight = ItemDetails.Weight;

	LoadMesh();
	MeshComponent->SetAnimInstanceClass(AnimInstanceClass);

	bInitialized = true;
}

void ASRBodyPart::SetBodyPartMeshParameters(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	}
}

void ASRBodyPart::LoadMesh()
{
	USRAssetManager& AssetManager = USRAssetManager::Get();
	TWeakObjectPtr<USkeletalMeshComponent> WeakMeshComponent = MeshComponent;
	bMeshLoaded = false;
	AssetManager.SetSkeletalMeshAsync(BaseMesh, WeakMeshComponent, FSimpleDelegate::CreateWeakLambda(this, [this]() 
	{
		OnMeshLoaded();
	}));
}

void ASRBodyPart::OnMeshLoaded()
{
	bMeshLoaded = true;
	AttachBodyParts();
}

void ASRBodyPart::AddAttachmentBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{	
		if (bMeshLoaded)
		{
			BodyPart->AttachToBodyPart(this);	
		}
		else
		{
			AttachmentBodyParts.Add(BodyPart);
		}
	}
}

void ASRBodyPart::AttachBodyParts()
{
	// Attach all attachment body parts to this body part
	for (TWeakObjectPtr<ASRBodyPart> BodyPart : AttachmentBodyParts)
	{
		if (BodyPart.IsValid())
		{
			BodyPart->AttachToBodyPart(this);
			AttachmentBodyParts.Remove(BodyPart);
		}
	}
}

void ASRBodyPart::AttachToBodyPart(ASRBodyPart* BodyPart)
{
	if (BodyPart)
	{
		if (BodyPart->MeshComponent)
		{
			AttachToComponent(BodyPart->MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}
