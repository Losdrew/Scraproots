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

	UFUNCTION(BlueprintCallable, Category = "Product")
	FSRProductDefinition GetProductDefinition(const FGameplayTag& ProductTag) const;

	UFUNCTION(BlueprintCallable, Category = "Product")
	void GetAllUsableBodyParts(const FGameplayTag& BodyPartTag, TArray<FSRProductDefinition>& OutArray) const;


	FSRProductDefinition* FindProductDefinition(const FGameplayTag& ProductTag) const;
	void GetProductDefinitions(const FGameplayTagContainer& ProductTags, TArray<const FSRProductDefinition*>& OutArray) const;
	UDataTable* GetProductDefinitionsTable() const { return ProductsConfig.ProductDefinitionsTable; }

private:
	TMap<FGameplayTag, FSRProductDefinition*> ProductDefinitionMap;
	
	FSRProductsConfig ProductsConfig;
};
