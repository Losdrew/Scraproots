// Fill out your copyright notice in the Description page of Project Settings.

#include "Product/SRProductManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRProductManager, All, All);

void USRProductManager::Initialize(const FSRProductsConfig& InConfig)
{
	ProductsConfig = InConfig;

	if (ProductsConfig.ProductDefinitionsTable)
	{
		const FString ContextString(TEXT("USRProductManager::Initialize"));
		TArray<FSRProductDefinition*> AllRows;
		ProductsConfig.ProductDefinitionsTable->GetAllRows<FSRProductDefinition>(ContextString, AllRows);

		for (FSRProductDefinition* RowData : AllRows)
		{
			if (RowData)
			{
				ProductDefinitionMap.Add(RowData->ProductTag, RowData);
			}
		}
	}
	else
	{
		UE_LOG(LogSRProductManager, Error, TEXT("ProductDefinitionsTable is not set in the SRProductManager!"));
	}
}

const FSRProductDefinition* USRProductManager::FindProductDefinition(const FGameplayTag& ProductTag) const
{
	if (!ProductsConfig.ProductDefinitionsTable)
	{
		UE_LOG(LogSRProductManager, Error, TEXT("ProductDefinitionsTable is not set in the SRProductManager!"));
		return nullptr;
	}

	if (FSRProductDefinition* const* FoundDefinition = ProductDefinitionMap.Find(ProductTag))
	{
		return *FoundDefinition;
	}

	return nullptr;
}

void USRProductManager::GetProductDefinitions(const FGameplayTagContainer& ProductTags, TArray<const FSRProductDefinition*>& OutArray) const
{
	for (FGameplayTag ProductTag : ProductTags)
	{
		if (const FSRProductDefinition* ProductDefinition = FindProductDefinition(ProductTag))
		{
			OutArray.Add(ProductDefinition);
		}
	}
}