// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Core/SRGameplayEventRouter.h"
#include "SRProductTypes.generated.h"

UENUM(BlueprintType)
enum class ESRProductCategory : uint8
{
	BodyPart	UMETA(DisplayName = "Body Part"),
	Consumable	UMETA(DisplayName = "Consumable")
};

UCLASS(BlueprintType, Blueprintable)
class SCRAPROOTS_API USRProductSchemaData : public UDataAsset
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRInventoryItemDetails
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRProductDefinition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ProductTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESRProductCategory CategoryID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float Price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USRProductSchemaData> Schema;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShopItem = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInventoryItem = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bInventoryItem", EditConditionHides))
	FSRInventoryItemDetails InventoryItemDetails;

	bool IsValid() const
	{
		return ProductTag != FGameplayTag::EmptyTag && !DisplayName.IsEmpty();
	}
};

USTRUCT(BlueprintType)
struct SCRAPROOTS_API FSRProductsConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop Configuration", meta = (RowType = "Script/Scraproots.SRProductDefinition"))
	TObjectPtr<UDataTable> ProductDefinitionsTable = nullptr;
};