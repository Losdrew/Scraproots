// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "SRGenerateAllyTileIndices.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRGenerateAllyTileIndices : public UObject
{
	GENERATED_BODY()

public:
	USRGenerateAllyTileIndices();

	UFUNCTION(BlueprintCallable, Category = "Random Generation")
	static TArray<int32> GenerateAllyTileIndices(int32 NumberOfUnits, int32 GridYSize);
};
