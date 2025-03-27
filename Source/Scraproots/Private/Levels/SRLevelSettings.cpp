// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SRLevelSettings)

FName USRLevelSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
