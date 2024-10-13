// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/SRModularCharacter.h"

#include "Components/CapsuleComponent.h"
#include "ModularCharacter/Assembly/SRCharacterPartsComponent.h"

ASRModularCharacter::ASRModularCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CharacterPartsComponent = CreateDefaultSubobject<USRCharacterPartsComponent>(TEXT("Character Parts Component"));
}

void ASRModularCharacter::InitializeFromPreset(const FSRModularCharacterPreset& Preset)
{
	if (CharacterPartsComponent == nullptr)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("ASRModularCharacter::InitializeFromPreset: CharacterPartsComponent is null"));
		return;
	}

	CharacterPartsComponent->Initialize(&BodyParts);
	CharacterPartsComponent->AddBodyPart(Preset.LeftArmPreset);
	CharacterPartsComponent->AddBodyPart(Preset.RightArmPreset);
	CharacterPartsComponent->AddBodyPart(Preset.LegsPreset);
	CharacterPartsComponent->AddBodyPart(Preset.HeadPreset);
	CharacterPartsComponent->AddBodyPart(Preset.TorsoPreset);
	CharacterPartsComponent->AddBodyPart(Preset.SpinePreset);
}
