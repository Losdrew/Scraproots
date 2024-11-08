// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ModularCharacter/Parts/SRBodyPart_Arm.h"
#include "ModularCharacter/Parts/SRBodyPart_Head.h"
#include "ModularCharacter/Parts/SRBodyPart_Leg.h"
#include "ModularCharacter/Parts/SRBodyPart_Spine.h"
#include "ModularCharacter/Parts/SRBodyPart_Torso.h"
#include "ModularCharacter/SRModularCharacterTypes.h"
#include "SRModularCharacter.generated.h"

class USRCharacterPartsComponent;

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRModularCharacterPreset
{
	GENERATED_BODY()

	virtual ~FSRModularCharacterPreset() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Arm LeftArmPreset{ESRBodyPartType::LeftArm};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Arm RightArmPreset{ESRBodyPartType::RightArm};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Leg LegsPreset{ESRBodyPartType::Legs};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Head HeadPreset{ESRBodyPartType::Head};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Torso TorsoPreset{ESRBodyPartType::Torso};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	FSRBodyPartPreset_Spine SpinePreset{ESRBodyPartType::Spine};
};

UCLASS(Abstract)
class SCRAPROOTS_API ASRModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRModularCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void InitializeFromPreset(const FSRModularCharacterPreset& Preset);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USRCharacterPartsComponent> CharacterPartsComponent;

protected:
	UPROPERTY()
	TArray<TObjectPtr<ASRBodyPart>> BodyParts;
};
