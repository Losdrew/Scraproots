// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/SRGameplayTags.h"

FGameplayTag FSRTag_Event::Inventory_ItemsChanged()
{
	static FGameplayTag Result = FGameplayTag::RequestGameplayTag(FName("Event.Inventory.ItemsChanged"));
	return Result;
}
