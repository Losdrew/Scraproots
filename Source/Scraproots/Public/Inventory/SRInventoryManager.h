// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Product/SRProductTypes.h"
#include "SRInventoryManager.generated.h"

struct FSRInventoryItem;

UCLASS()
class SCRAPROOTS_API USRInventoryManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddProduct(const FGameplayTag& ProductTag);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddProducts(const FGameplayTagContainer& ProductTags);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(const FGuid& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FSRInventoryItem>& GetInventoryItems() const { return InventoryItems; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetNumItems() const { return InventoryItems.Num(); }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetItemsByCategory(ESRProductCategory Category, TArray<FSRInventoryItem>& OutItems) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryGetInventoryItemByProductTag(const FGameplayTag& ProductTag, FSRInventoryItem& OutItem);

	// Internal helper to find an inventory item
	FSRInventoryItem* FindInventoryItem(const FGuid& ItemID);

	// Internal helper to find an inventory item by product tag
	FSRInventoryItem* FindInventoryItemByProductTag(const FGameplayTag& ProductTag);

private:
	void ClearData();

	UFUNCTION()
	void HandleGameplayEvent(const FSRGameplayEvent& Event);

private:
	UPROPERTY()
	TArray<FSRInventoryItem> InventoryItems;
};