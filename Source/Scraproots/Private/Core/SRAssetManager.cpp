// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SRAssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRAssetManager, Log, All);

USRAssetManager& USRAssetManager::Get()
{
	check(GEngine);

	if (USRAssetManager* Singleton = Cast<USRAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogSRAssetManager, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to SRAssetManager!"));

	// Fatal error above prevents this from being called.
	return *NewObject<USRAssetManager>();
}

void USRAssetManager::SetSkeletalMeshAsync(TSoftObjectPtr<USkeletalMesh> MeshToLoad, TWeakObjectPtr<USkeletalMeshComponent> MeshComponentToSet, TDelegate<void()> OnMeshLoadedCallback)
{
	if (MeshComponentToSet != nullptr)
	{
		if (!MeshToLoad.IsNull())
		{
			FStreamableManager& Streamable = GetStreamableManager();

			Streamable.RequestAsyncLoad(MeshToLoad.ToSoftObjectPath(),
				[this, MeshToLoad, MeshComponentToSet, OnMeshLoadedCallback]()
				{
					if (USkeletalMesh* LoadedMesh = MeshToLoad.Get())
					{
						if (MeshComponentToSet.IsValid())
						{
							MeshComponentToSet->SetSkeletalMesh(LoadedMesh, true);
						}
						OnMeshLoadedCallback.ExecuteIfBound();
					}
					else
					{
						FString MeshName = MeshToLoad.ToSoftObjectPath().ToString();
						UE_LOG(LogSRAssetManager, Warning, TEXT("Failed to load skeletal mesh {0}."), *MeshName);
					}
				});
		}
		else
		{
			// Assuming null mesh is a valid state and we should clear the mesh
			MeshComponentToSet->SetSkeletalMesh(nullptr);
			return;
		}
	}
	else
	{
		UE_LOG(LogSRAssetManager, Warning, TEXT("MeshComponentToSet is null"));
		return;
	}
}
