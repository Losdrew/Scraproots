// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/AssetManager.h"
#include "SRAssetManager.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSRAssetManager, Log, All);

UCLASS()
class SCRAPROOTS_API USRAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Returns the AssetManager singleton object.
	static USRAssetManager& Get();

	// Asynchronously loads a class referenced by a TSoftClassPtr and calls the callback when the class is loaded.
	template <typename ClassType>
	void LoadClassAsync(const TSoftClassPtr<ClassType>& ClassPointer, TDelegate<void(TSubclassOf<ClassType>)> OnClassLoaded);

	// Asynchronously sets skeletal mesh on the passed in SkeletalMeshComponent.
	// Also provides a callback to be called when the mesh is loaded.
	void SetSkeletalMeshAsync(TSoftObjectPtr<USkeletalMesh> MeshToLoad, TWeakObjectPtr<USkeletalMeshComponent> MeshComponentToSet, TDelegate<void()> OnMeshLoadedCallback = nullptr);
};

template <typename ClassType>
void USRAssetManager::LoadClassAsync(const TSoftClassPtr<ClassType>& ClassPointer, TDelegate<void(TSubclassOf<ClassType>)> OnClassLoaded)
{
	const FSoftObjectPath& ClassPath = ClassPointer.ToSoftObjectPath();

	if (!ClassPath.IsValid())
	{
		FString ClassName = ClassPath.ToString();
		UE_LOG(LogSRAssetManager, Warning, TEXT("Invalid asset path for class %s."), *ClassName);
		return;
	}

	UClass* LoadedClass = ClassPointer.Get();
	if (LoadedClass)
	{
		OnClassLoaded.ExecuteIfBound(LoadedClass);
		return;
	}

	GetStreamableManager().RequestAsyncLoad(ClassPath, FStreamableDelegate::CreateLambda([ClassPointer, OnClassLoaded]()
	{
        UClass* LoadedClass = ClassPointer.Get();
        if (LoadedClass)
		{
			OnClassLoaded.ExecuteIfBound(LoadedClass);
        }
        else
        {
			FString ClassName = ClassPointer.ToSoftObjectPath().ToString();
            UE_LOG(LogSRAssetManager, Warning, TEXT("Failed to load class %s."), *ClassName);
        } 
	}));
}