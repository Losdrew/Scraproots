// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SRCharacterPartsComponent.generated.h"

enum class ESRBodyPartType : uint8;
struct FSRModularCharacterPreset;
struct FSRBodyPartPreset;
class ASRBodyPart;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBodyPartChangedSignature, ASRBodyPart*, BodyPart);

// Handles spawning and managing body parts for a modular character
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class USRCharacterPartsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USRCharacterPartsComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter")
	void SetBodyPartsFromPreset(const FSRModularCharacterPreset& Preset);

	// Sets a body part on the character, replaces if it already exists
	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	void SetBodyPart(const FSRBodyPartPreset& PartPreset);

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	void RemoveBodyPart(ESRBodyPartType BodyPartType);

	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	ASRBodyPart* GetBodyPartByPartType(ESRBodyPartType PartType) const;

	// Gets all body part instances currently attached to the character
	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	const TMap<ESRBodyPartType, ASRBodyPart*> GetAllBodyParts() const;

	// Attaches all body parts to the character
	UFUNCTION(BlueprintCallable, Category = "ModularCharacter|Parts")
	void AttachBodyParts();

public:
	UPROPERTY(BlueprintAssignable, Category = "ModularCharacter|Parts")
	FOnBodyPartChangedSignature OnBodyPartAddedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "ModularCharacter|Parts")
	FOnBodyPartChangedSignature OnBodyPartRemovedDelegate;

protected:
	UFUNCTION()
	void OnBodyPartAdded(ASRBodyPart* BodyPart);

	UFUNCTION()
	void OnBodyPartRemoved(ASRBodyPart* BodyPart);

	// If the parent actor is derived from ACharacter, returns the Mesh component, otherwise nullptr
	USkeletalMeshComponent* GetParentMeshComponent() const;

	virtual void OnActorVisibilityChanged() override;

protected:
	UPROPERTY()
	TMap<ESRBodyPartType, TObjectPtr<ASRBodyPart>> BodyParts;

private:
	void DetachBodyPart(ASRBodyPart* BodyPart);
};
