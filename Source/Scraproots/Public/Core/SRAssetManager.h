// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/AssetManager.h"
#include "SRAssetManager.generated.h"

UCLASS()
class SCRAPROOTS_API USRAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Returns the AssetManager singleton object.
	static USRAssetManager& Get();

	// Asynchronously sets skeletal mesh on the passed in SkeletalMeshComponent
	void SetSkeletalMeshAsync(TSoftObjectPtr<USkeletalMesh> MeshToLoad, USkeletalMeshComponent* MeshComponentToSet);

	// Asynchronously sets skeletal mesh on the passed in SkeletalMeshComponent
	void SetStaticMeshAsync(TSoftObjectPtr<UStaticMesh> MeshToLoad, UStaticMeshComponent* MeshComponentToSet);
};
