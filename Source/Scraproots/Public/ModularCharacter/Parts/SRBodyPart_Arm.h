// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularCharacter/Parts/SRBodyPart.h"
#include "SRBodyPart_Arm.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema_Arm : public FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	FSRBodyPartSchema_Arm();
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const override { return ArmClass; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (AllowedClasses = "/Script/Scraproots.SRBodyPart_Arm"))
	TSubclassOf<ASRBodyPart> ArmClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftClassPtr<USRAnimInstance> AnimInstanceClassLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftClassPtr<USRAnimInstance> AnimInstanceClassRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> MeshLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocketLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	TSoftObjectPtr<USkeletalMesh> MeshRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart")
	FName AttachmentSocketRight;
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRArmSchemaData : public USRBodyPartSchemaData
{
	GENERATED_BODY()

	virtual const FSRBodyPartSchema& GetBodyPartSchema() const override { return ArmSchema; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
	FSRBodyPartSchema_Arm ArmSchema;
};

UCLASS()
class SCRAPROOTS_API ASRBodyPart_Arm : public ASRBodyPart
{
	GENERATED_BODY()

public:
	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset) override;

protected:
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart) override;
};
