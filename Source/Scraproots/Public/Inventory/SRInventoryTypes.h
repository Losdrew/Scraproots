// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Product/SRProductTypes.h"
#include "SRInventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRInventoryItem
{
	GENERATED_BODY()

	// Unique identifier for the inventory item
	UPROPERTY(BlueprintReadOnly, meta = (IgnoreForMemberInitializationTest))
	FGuid ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ProductTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESRProductCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSRProductDefinition ProductDefinition;

	FSRInventoryItem()
		: ItemID(FGuid::NewGuid()),
		  ProductTag(FGameplayTag::EmptyTag),
		  Category(ESRProductCategory::BodyPart),
		  ProductDefinition()
	{
	}

	FSRInventoryItem(const FSRProductDefinition& ProductDefinition)
		: ItemID(FGuid::NewGuid()),
		  ProductTag(ProductDefinition.ProductTag),
		  Category(ProductDefinition.CategoryID),
		  ProductDefinition(ProductDefinition)
	{
	}

	bool IsValid() const
	{
		return ProductTag != FGameplayTag::EmptyTag;
	}

	bool operator==(const FSRInventoryItem& Other) const
	{
		return ItemID == Other.ItemID;
	}
};