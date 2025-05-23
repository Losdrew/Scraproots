// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/SRInventoryManager.h"

#include "Core/SRStatics.h"
#include "Core/SRGameplayTags.h"
#include "Inventory/SRInventoryTypes.h"
#include "Product/SRProductManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRInventoryManager, Log, All);

void USRInventoryManager::Initialize()
{
	InventoryConfig = GetDefault<USRInventorySettings>()->InventoryConfig;

	if (InventoryConfig.InitialItems.Num() > 0)
	{
		AddProducts(InventoryConfig.InitialItems);
	}
}

bool USRInventoryManager::AddProduct(const FGameplayTag& ProductTag)
{
	const FSRProductDefinition* ProductDef = USRStatics::GetProductManager(this)->FindProductDefinition(ProductTag);
	if (!ProductDef)
	{
		UE_LOG(LogSRInventoryManager, Error, TEXT("AddItem: Product definition not found for tag %s."), *ProductTag.ToString());
		return false;
	}

	FSRInventoryItem NewItem(*ProductDef);

	InventoryItems.Add(NewItem);
	UE_LOG(LogSRInventoryManager, Log, TEXT("AddItem: Added item %s to inventory."), *ProductDef->DisplayName.ToString());
	USRStatics::BroadcastGameplayEvent(this, {FSRTag_Event::Inventory_ItemsChanged(), ""});

	return true;
}

void USRInventoryManager::AddProducts(const FGameplayTagContainer& ProductTags)
{
	for (const FGameplayTag& ProductTag : ProductTags)
	{
		AddProduct(ProductTag);
	}
}

bool USRInventoryManager::RemoveItem(const FGuid& ItemID)
{
	const FSRInventoryItem* Item = FindInventoryItem(ItemID);
	if (!Item)
	{
		UE_LOG(LogSRInventoryManager, Warning, TEXT("RemoveItem: Item with ID %s not found."), *ItemID.ToString());
		return false;
	}

	InventoryItems.RemoveSingle(*Item);
	UE_LOG(LogSRInventoryManager, Log, TEXT("RemoveItem: Removed item %s from inventory."), *Item->ProductTag.ToString());
	USRStatics::BroadcastGameplayEvent(this, {FSRTag_Event::Inventory_ItemsChanged(), ""});

	return true;
}

void USRInventoryManager::GetItemsByCategory(const ESRProductCategory Category, TArray<FSRInventoryItem>& OutItems) const
{
	OutItems.Empty();
	for (const FSRInventoryItem& Item : InventoryItems)
	{
		if (Item.Category == Category)
		{
			OutItems.Add(Item);
		}
	}
}

bool USRInventoryManager::TryGetInventoryItemByProductTag(const FGameplayTag& ProductTag, FSRInventoryItem& OutItem)
{
	if (const FSRInventoryItem* Item = FindInventoryItemByProductTag(ProductTag))
	{
		OutItem = *Item;
		return true;
	}
	return false;
}

FSRInventoryItem* USRInventoryManager::FindInventoryItem(const FGuid& ItemID)
{
	for (FSRInventoryItem& Item : InventoryItems)
	{
		if (Item.ItemID == ItemID)
		{
			return &Item;
		}
	}
	return nullptr;
}

FSRInventoryItem* USRInventoryManager::FindInventoryItemByProductTag(const FGameplayTag& ProductTag)
{
	for (FSRInventoryItem& Item : InventoryItems)
	{
		if (Item.ProductTag == ProductTag)
		{
			return &Item;
		}
	}
	return nullptr;
}

void USRInventoryManager::ClearData()
{
	InventoryItems.Empty();
	USRStatics::BroadcastGameplayEvent(this, {FSRTag_Event::Inventory_ItemsChanged(), ""});
}
