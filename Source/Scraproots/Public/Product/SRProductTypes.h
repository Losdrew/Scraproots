// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Core/SRGameplayEventRouter.h"
#include "Abilities/SRAbility.h"
#include "SRProductTypes.generated.h"

class ASRAbility;

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
struct SCRAPROOTS_API FSRItemDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ForceInlineRow))
	TMap<FGameplayTag, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ASRAbility>> Abilities;

	// Weight used for random generation
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Weight = 0;
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

	// Description of stats/attributes/abilities that this product has.
	// This is used to display the product's stats in the UI.
	// Might not reflect the actual stats of the product.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = "true"))
	FText StatsText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESRProductCategory CategoryID = ESRProductCategory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float Price = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USRProductSchemaData> Schema;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (FullyExpand = "true"))
	FSRItemDetails ItemDetails;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShopItem = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInventoryItem = true;

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