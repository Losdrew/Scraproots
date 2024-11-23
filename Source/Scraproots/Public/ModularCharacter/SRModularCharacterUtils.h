// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRModularCharacterUtils.generated.h"

struct FGameplayTag;
struct FSRProductDefinition;
class USRBodyPartSchemaData;
class USRProductSchemaData;

UCLASS()
class SCRAPROOTS_API USRModularCharacterUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Modular Character", meta = (WorldContext = "WorldContextObject"))
	static USRBodyPartSchemaData* GetBodyPartSchemaDataByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag);

	static FSRProductDefinition* GetProductDefinitionByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag);
	static USRProductSchemaData* GetProductSchemaDataByProductTag(const UObject* WorldContextObject, FGameplayTag ProductTag);
};
