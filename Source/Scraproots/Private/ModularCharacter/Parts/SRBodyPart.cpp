// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart.h"

#include "ModularCharacter/SRModularCharacterTypes.h"

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
	USRBodyPartSchemaData* SchemaData = Preset.GetBodyPartSchemaData();
	if (SchemaData == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRBodyPart::InitializeFromPreset: SchemaData is null"));
		return;
	}

	const FSRBodyPartSchema& BodyPartSchema = SchemaData->GetBodyPartSchema();

	BodyPartType = Preset.BodyPartType;
	BodyPartName = BodyPartSchema.Name;
	Rarity = BodyPartSchema.Rarity;
	Stats = BodyPartSchema.Stats;

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
