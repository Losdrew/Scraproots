// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTags.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "Animation/SRAnimInstance.h"
#include "Product/SRProductTypes.h"
#include "Abilities/SRAbility.h"
#include "SRBodyPart.generated.h"

class ASRBodyPart;

DECLARE_MULTICAST_DELEGATE(FSROnMeshLoadedSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FSROnBodyPartAttachedSignature, ASRBodyPart*);

// Defines a body part (general configuration)
USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRBodyPartSchema
{
	GENERATED_BODY()

public:
	FSRBodyPartSchema();
	virtual ~FSRBodyPartSchema() = default;
	virtual TSubclassOf<ASRBodyPart> GetBodyPartClass() const;
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "BodyPart"))
	FGameplayTag ProductTag = FGameplayTag::EmptyTag;

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
	virtual void AttachToMeshComponent(USkeletalMeshComponent* InMeshComponent);
	virtual void AddAttachmentBodyPart(ASRBodyPart* BodyPart);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	FGameplayTag ProductTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	ESRBodyPartType BodyPartType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	FName AttachmentSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	TSoftClassPtr<USRAnimInstance> AnimInstanceClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	TMap<FGameplayTag, float> Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	TArray<TSubclassOf<ASRAbility>> Abilities;

	// Weight used for random generation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BodyPart")
	int32 Weight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cosmetics")
	TSoftObjectPtr<USkeletalMesh> BaseMesh;

	FSROnBodyPartAttachedSignature OnBodyPartAttachedDelegate;

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
	virtual void AttachToBodyPart(ASRBodyPart* BodyPart);

protected:
	FSROnMeshLoadedSignature OnMeshLoadedDelegate;

	bool bMeshLoaded = false;
};
