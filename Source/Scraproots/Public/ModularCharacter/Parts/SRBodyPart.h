// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTags.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "Animation/SRAnimInstance.h"
#include "Product/SRProductTypes.h"
#include "SRBodyPart.generated.h"

class ASRBodyPart;

// Defines a body part (general configuration)
USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	virtual ~FSRBodyPartSchema() = default;
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (DisplayPriority = 1))
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (DisplayPriority = 1))
	ESRRarity Rarity = ESRRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPart", meta = (ForceInlineRow))
	TMap<FGameplayTag, float> Stats;
};

UCLASS(Abstract)
class SCRAPROOTS_API USRBodyPartSchemaData : public USRProductSchemaData
{
	GENERATED_BODY()

public:
	virtual const FSRBodyPartSchema& GetBodyPartSchema() const { return BodyPartSchema; };

private:
	// Only used for default GetBodyPartSchema implementation to be able to return a reference
	FSRBodyPartSchema BodyPartSchema;
};

// Defines an instance of a body part (specific configuration)
USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartPreset
{
	GENERATED_BODY()

public:
	FSRBodyPartPreset(){};
	FSRBodyPartPreset(ESRBodyPartType PartType) : BodyPartType(PartType){};
	virtual ~FSRBodyPartPreset() = default;

	virtual USRBodyPartSchemaData* GetBodyPartSchemaData() const { return nullptr; };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESRBodyPartType BodyPartType = ESRBodyPartType::None;
};

// Instance of a body part
UCLASS(Abstract)
class SCRAPROOTS_API ASRBodyPart : public AActor
{
	GENERATED_BODY()

public:
	ASRBodyPart();

	virtual void InitializeFromPreset(const FSRBodyPartPreset& Preset);
	virtual void AddAttachmentBodyPart(ASRBodyPart* BodyPart);

public:
	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	FText BodyPartName;

	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	ESRRarity Rarity;

	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	ESRBodyPartType BodyPartType;

	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	FName AttachmentSocket;

	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	TSubclassOf<USRAnimInstance> AnimInstanceClass;

	UPROPERTY(BlueprintReadOnly, Category = "BodyPart")
	TMap<FGameplayTag, float> Stats;

	UPROPERTY(BlueprintReadOnly, Category = "Cosmetics")
	TSoftObjectPtr<USkeletalMesh> BaseMesh;

	bool bInitialized = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

protected:
	// Sets default parameters for a body part mesh
	virtual void SetBodyPartMeshParameters(USkeletalMeshComponent* MeshComponent);

	virtual void LoadMesh();
	virtual void OnMeshLoaded();
	virtual void AttachBodyParts();
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart);

protected:
	// Body parts that should be attached to this body part
	TArray<TWeakObjectPtr<ASRBodyPart>> AttachmentBodyParts;
};
