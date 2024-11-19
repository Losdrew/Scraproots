// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SRProductTypes.h"
#include "SRProductManager.generated.h"

UCLASS()
class SCRAPROOTS_API USRProductManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(const FSRProductsConfig& InConfig);

	const FSRProductDefinition* FindProductDefinition(const FGameplayTag& ProductTag) const;
	void GetProductDefinitions(const FGameplayTagContainer& ProductTags, TArray<const FSRProductDefinition*>& OutArray) const;
	UDataTable* GetProductDefinitionsTable() const { return ProductsConfig.ProductDefinitionsTable; }

private:
	TMap<FGameplayTag, FSRProductDefinition*> ProductDefinitionMap;
	
	FSRProductsConfig ProductsConfig;
};
