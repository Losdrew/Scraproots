// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SRCharacterPartsComponent.generated.h"

enum class ESRBodyPartType : uint8;
struct FSRBodyPartPreset;
class ASRBodyPart;

// Handles spawning and managing body parts for a modular character
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class USRCharacterPartsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USRCharacterPartsComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void Initialize(TArray<TObjectPtr<ASRBodyPart>>* BodyParts);

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	void AddBodyPart(const FSRBodyPartPreset& PartPreset);

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	void RemoveBodyPart(ESRBodyPartType BodyPartType);

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	ASRBodyPart* GetBodyPartByPartType(ESRBodyPartType PartType) const;

	// Gets all body part instances currently attached to the character
	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	TArray<ASRBodyPart*> GetAllBodyParts() const;

protected:
	// If the parent actor is derived from ACharacter, returns the Mesh component, otherwise nullptr
	USkeletalMeshComponent* GetParentMeshComponent() const;

private:
	void AttachBodyPart(ASRBodyPart* BodyPart);
	void DetachBodyPart(ASRBodyPart* BodyPart);

private:
	TArray<TObjectPtr<ASRBodyPart>>* BodyPartsPtr = nullptr;
};
