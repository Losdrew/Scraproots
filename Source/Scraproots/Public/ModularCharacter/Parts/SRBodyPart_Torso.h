// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/Parts/SRBodyPart.h"
#include "SRBodyPart_Torso.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema_Torso : public FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	FSRBodyPartSchema_Torso();
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const override { return TorsoClass; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (AllowedClasses = "/Script/Scraproots.SRBodyPart_Torso"))
	TSubclassOf<ASRBodyPart> TorsoClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocket;
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRTorsoSchemaData : public USRBodyPartSchemaData
{
	GENERATED_BODY()

	virtual const FSRBodyPartSchema& GetBodyPartSchema() const override { return TorsoSchema; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRBodyPartSchema_Torso TorsoSchema;
};

UCLASS()
class SCRAPROOTS_API ASRBodyPart_Torso : public ASRBodyPart
{
	GENERATED_BODY()

public:
	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset) override;

protected:
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AttachToLegs(ASRBodyPart* BodyPart);
};
