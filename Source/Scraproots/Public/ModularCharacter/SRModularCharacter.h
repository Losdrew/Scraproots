// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ModularCharacter/Parts/SRBodyPart.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "SRModularCharacter.generated.h"

class USRCharacterPartsComponent;
class ASRBodyPart;

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRModularCharacterPreset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset LeftArmPreset{ESRBodyPartType::LeftArm};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset RightArmPreset{ESRBodyPartType::RightArm};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset LegsPreset{ESRBodyPartType::Legs};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset HeadPreset{ESRBodyPartType::Head};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset TorsoPreset{ESRBodyPartType::Torso};
};

UCLASS(Abstract)
class SCRAPROOTS_API ASRModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRModularCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void InitializeFromPreset(const FSRModularCharacterPreset& Preset);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USRCharacterPartsComponent> CharacterPartsComponent;
};
