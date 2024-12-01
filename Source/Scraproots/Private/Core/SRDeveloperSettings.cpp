// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SRDeveloperSettings)

USRDeveloperSettings::USRDeveloperSettings()
{
}


FName USRDeveloperSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}

#if WITH_EDITOR
void USRDeveloperSettings::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
}

void USRDeveloperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void USRDeveloperSettings::PostReloadConfig(FProperty* PropertyThatWasLoaded)
{
	Super::PostReloadConfig(PropertyThatWasLoaded);
}

void USRDeveloperSettings::PostInitProperties()
{
	Super::PostInitProperties();
}
#endif