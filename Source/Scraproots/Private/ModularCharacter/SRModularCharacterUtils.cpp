// Fill out your copyright notice in the Description page of Project Settings.

#include "ModularCharacter/SRModularCharacterUtils.h"

#include "GameplayTagContainer.h"
#include "Core/SRStatics.h"
#include "Core/SRDeveloperSettings.h"
#include "Product/SRProductTypes.h"
#include "Product/SRProductManager.h"
#include "ModularCharacter/Parts/SRBodyPart.h"
#include "ModularCharacter/SRModularCharacterTypes.h"

USRBodyPartSchemaData* USRModularCharacterUtils::GetBodyPartSchemaDataByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag)
{
	if (USRProductSchemaData* ProductSchemaData = GetProductSchemaDataByProductTag(WorldContextObject, ProductTag))
	{
		return Cast<USRBodyPartSchemaData>(ProductSchemaData);
	}
	return nullptr;
}

ESRBodyPartType USRModularCharacterUtils::GetBodyPartTypeByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag)
{
	const USRDeveloperSettings* DeveloperSettings = GetDefault<USRDeveloperSettings>();
	if (!DeveloperSettings)
	{
		UE_LOG(LogSRModularCharacter, Error, TEXT("USRModularCharacterUtils::GetBodyPartTypeByProductTag: Developer settings not found"));
		return ESRBodyPartType::None;
	}

	if (ProductTag.MatchesTag(DeveloperSettings->ModularCharacterConfig.GenericHeadTag))
	{
		return ESRBodyPartType::Head;
	}
	if (ProductTag.MatchesTag(DeveloperSettings->ModularCharacterConfig.GenericTorsoTag))
	{
		return ESRBodyPartType::Torso;
	}
	if (ProductTag.MatchesTag(DeveloperSettings->ModularCharacterConfig.GenericLeftArmTag))
	{
		return ESRBodyPartType::LeftArm;
	}
	if (ProductTag.MatchesTag(DeveloperSettings->ModularCharacterConfig.GenericRightArmTag))
	{
		return ESRBodyPartType::RightArm;
	}
	if (ProductTag.MatchesTag(DeveloperSettings->ModularCharacterConfig.GenericLegsTag))
	{
		return ESRBodyPartType::Legs;
	}

	if (ProductTag != FGameplayTag::EmptyTag)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("USRModularCharacterUtils::GetBodyPartTypeByProductTag: Body part type not found for tag %s"), *ProductTag.ToString());
	}

	return ESRBodyPartType::None;
}

FSRProductDefinition* USRModularCharacterUtils::GetProductDefinitionByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag)
{
	if (USRProductManager* ProductManager = USRStatics::GetProductManager(WorldContextObject))
	{
		if (FSRProductDefinition* ProductDefinition = ProductManager->FindProductDefinition(ProductTag))
		{
			return ProductDefinition;
		}
	}

	if (ProductTag != FGameplayTag::EmptyTag)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("USRModularCharacterUtils::GetProductDefinitionByProductTag: Product definition not found for tag %s"), *ProductTag.ToString());
	}

	return nullptr;
}

USRProductSchemaData* USRModularCharacterUtils::GetProductSchemaDataByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag)
{
	if (const FSRProductDefinition* ProductDefinition = GetProductDefinitionByProductTag(WorldContextObject, ProductTag))
	{
		return ProductDefinition->Schema;
	}

	if (ProductTag != FGameplayTag::EmptyTag)
	{
		UE_LOG(LogSRModularCharacter, Warning, TEXT("USRModularCharacterUtils::GetProductSchemaDataByProductTag: Product schema not found for tag %s"), *ProductTag.ToString());
	}

	return nullptr;
}
