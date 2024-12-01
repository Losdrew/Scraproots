// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/Parts/SRBodyPart.h"
#include "SRBodyPart_Leg.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema_Leg : public FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	FSRBodyPartSchema_Leg();
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const override { return LegClass; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (AllowedClasses = "/Script/Scraproots.SRBodyPart_Leg"))
	TSubclassOf<ASRBodyPart> LegClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftClassPtr<USRAnimInstance> AnimInstanceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocket;
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRLegSchemaData : public USRBodyPartSchemaData
{
	GENERATED_BODY()

	virtual const FSRBodyPartSchema& GetBodyPartSchema() const override { return LegSchema; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRBodyPartSchema_Leg LegSchema;
};

UCLASS()
class SCRAPROOTS_API ASRBodyPart_Leg : public ASRBodyPart
{
	GENERATED_BODY()

public:
	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset) override;

protected:
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart) override;
};
