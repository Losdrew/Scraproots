// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "SRModularCharacterTypes.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRModularCharacter, Log, All);

UENUM(BlueprintType)
enum class ESRBodyPartType : uint8
{
	None,
	Head,
	Torso,
	LeftArm,
	RightArm,
	Legs,
};

USTRUCT(BlueprintType)
struct FSRModularCharacterConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	TSubclassOf<class ASRBodyPart_Head> DefaultHeadClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	TSubclassOf<class ASRBodyPart_Torso> DefaultTorsoClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	TSubclassOf<class ASRBodyPart_Arm> DefaultArmClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	TSubclassOf<class ASRBodyPart_Leg> DefaultLegClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	FGameplayTag GenericHeadTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	FGameplayTag GenericTorsoTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	FGameplayTag GenericLeftArmTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	FGameplayTag GenericRightArmTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modular Character")
	FGameplayTag GenericLegsTag;
};