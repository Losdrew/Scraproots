// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/SRInventorySettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SRInventorySettings)

FName USRInventorySettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
