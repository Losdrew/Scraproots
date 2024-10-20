// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/Parts/SRBodyPart.h"
#include "SRBodyPart_Head.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema_Head : public FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const override { return HeadClass; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (AllowedClasses = "/Script/Scraproots.SRBodyPart_Head"))
	TSubclassOf<ASRBodyPart> HeadClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSubclassOf<USRAnimInstance> AnimInstanceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocket;
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRHeadSchemaData : public USRBodyPartSchemaData
{
	GENERATED_BODY()

	virtual const FSRBodyPartSchema& GetBodyPartSchema() const override { return HeadSchema; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRBodyPartSchema_Head HeadSchema;
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartPreset_Head : public FSRBodyPartPreset
{
	GENERATED_BODY()

public:
	// Inherit constructors
	using FSRBodyPartPreset::FSRBodyPartPreset;

	virtual USRBodyPartSchemaData* GetBodyPartSchemaData() const override { return HeadSchemaDataAsset; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TObjectPtr<USRHeadSchemaData> HeadSchemaDataAsset;
};

UCLASS()
class SCRAPROOTS_API ASRBodyPart_Head : public ASRBodyPart
{
	GENERATED_BODY()

public:
	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset) override;

protected:
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart) override;
};
