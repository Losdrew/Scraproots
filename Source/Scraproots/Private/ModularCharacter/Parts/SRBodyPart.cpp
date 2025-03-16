// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/Parts/SRBodyPart.h"

#include "ModularCharacter/SRModularCharacterTypes.h"
#include "ModularCharacter/SRModularCharacterUtils.h"
#include "Product/SRProductTypes.h"
#include "Core/SRAssetManager.h"

FSRBodyPartSchema::FSRBodyPartSchema()
{
}

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

	bInitialized = true;
}

void ASRBodyPart::AttachToMeshComponent(USkeletalMeshComponent* InMeshComponent)
{
	if (InMeshComponent)
	{
		AttachToComponent(InMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void ASRBodyPart::SetBodyPartMeshParameters(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block);
		SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndProbe);
		SkeletalMeshComponent->bReceivesDecals = false;
	}
}

void ASRBodyPart::LoadMesh()
{
	bMeshLoaded = false;

	USRAssetManager& AssetManager = USRAssetManager::Get();
	TWeakObjectPtr<USkeletalMeshComponent> WeakMeshComponent = MeshComponent;
	AssetManager.SetSkeletalMeshAsync(BaseMesh, WeakMeshComponent, FSimpleDelegate::CreateWeakLambda(this, [this]() 
	{
		OnMeshLoaded();
	}));

	AssetManager.LoadClassAsync<UAnimInstance>(AnimInstanceClass, TDelegate<void(TSubclassOf<UAnimInstance>)>::CreateWeakLambda(this, [this](TSubclassOf<UAnimInstance> InLoadedAnimInstanceClass)
	{ 
		LoadedAnimInstanceClass = InLoadedAnimInstanceClass;
		MeshComponent->SetAnimInstanceClass(LoadedAnimInstanceClass);
	}));
}

void ASRBodyPart::OnMeshLoaded()
{
	MeshComponent->SetAnimInstanceClass(LoadedAnimInstanceClass);
	bMeshLoaded = true;
	OnMeshLoadedDelegate.Broadcast();
}

void ASRBodyPart::AddAttachmentBodyPart(ASRBodyPart* BodyPart)
{
	if (!BodyPart)
	{	
		return;
	}

	if (bMeshLoaded)
	{
		BodyPart->AttachToBodyPart(this);	
	}
	else
	{
		OnMeshLoadedDelegate.AddWeakLambda(this, [this, BodyPart]()
		{
			BodyPart->AttachToBodyPart(this);
		});
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
