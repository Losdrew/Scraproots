// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/Parts/SRBodyPart.h"
#include "SRBodyPart_Spine.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema_Spine : public FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const override { return SpineClass; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (AllowedClasses = "/Script/Scraproots.SRBodyPart_Spine"))
	TSubclassOf<ASRBodyPart> SpineClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocket;
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRSpineSchemaData : public USRBodyPartSchemaData
{
	GENERATED_BODY()

	virtual const FSRBodyPartSchema& GetBodyPartSchema() const override { return SpineSchema; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRBodyPartSchema_Spine SpineSchema;
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartPreset_Spine : public FSRBodyPartPreset
{
	GENERATED_BODY()

public:
	// Inherit constructors
	using FSRBodyPartPreset::FSRBodyPartPreset;

	virtual USRBodyPartSchemaData* GetBodyPartSchemaData() const override { return SpineSchemaDataAsset; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TObjectPtr<USRSpineSchemaData> SpineSchemaDataAsset;
};

UCLASS()
class SCRAPROOTS_API ASRBodyPart_Spine : public ASRBodyPart
{
	GENERATED_BODY()

public:
	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset) override;

protected:
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart) override;
};
