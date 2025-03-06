// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenerateEnemyTileIndices.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRGenerateEnemyTileIndices : public UObject
{
	GENERATED_BODY()

public:
	USRGenerateEnemyTileIndices();

	UFUNCTION(BlueprintCallable, Category = "Random Generation")
	static TArray<int32> GenerateEnemyTileIndices(int32 NumberOfUnits, int32 GridYSize);
};
