// Fill out your copyright notice in the Description page of Project Settings.

#include "Audio/SRAudioSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SRAudioSettings)

FName USRAudioSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
