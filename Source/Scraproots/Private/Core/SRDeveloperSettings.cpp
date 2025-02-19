// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SRDeveloperSettings)

FName USRDeveloperSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
