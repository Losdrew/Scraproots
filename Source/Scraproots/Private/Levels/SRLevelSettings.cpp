// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/SRLevelSettings.h"

USRLevelSettings* USRLevelSettings::Get()
{
	// Retrieve the singleton instance from the config system
	return GetMutableDefault<USRLevelSettings>();
}
