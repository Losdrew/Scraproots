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
				UE_LOG(LogSRProductManager, Warning, TEXT("Added Product: %s"), *RowData->ProductTag.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogSRProductManager, Error, TEXT("ProductDefinitionsTable is not set in the SRProductManager!"));
	}
}

FSRProductDefinition USRProductManager::GetProductDefinition(const FGameplayTag& ProductTag) const
{
	if (const FSRProductDefinition* ProductDefinition = FindProductDefinition(ProductTag))
	{
		return *ProductDefinition;
	}
	return FSRProductDefinition();
}

FSRProductDefinition* USRProductManager::FindProductDefinition(const FGameplayTag& ProductTag) const
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

void USRProductManager::GetAllUsableBodyParts(const FGameplayTag& BodyPartTag, TArray<FSRProductDefinition>& OutArray) const
{
	OutArray.Empty();
	int32 FoundCount = 0;

	UE_LOG(LogSRProductManager, Warning, TEXT("Searching for body parts with tag: %s"), *BodyPartTag.ToString());

	for (const TPair<FGameplayTag, FSRProductDefinition*>& Entry : ProductDefinitionMap)
	{
		if (Entry.Key.MatchesTag(BodyPartTag))
		{
			if (Entry.Key.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("BodyPart.Head.CuteRobot"))))
			{
				UE_LOG(LogSRProductManager, Warning, TEXT("Skipping CuteRobot Head: %s"), *Entry.Key.ToString());
				continue;  // Пропускаємо CuteRobot
			}

			OutArray.Add(*Entry.Value);
			FoundCount++;

			UE_LOG(LogSRProductManager, Warning, TEXT("Found Body Part: %s"), *Entry.Key.ToString());
		}
	}

	UE_LOG(LogSRProductManager, Warning, TEXT("Total found body parts: %d"), FoundCount);
}
