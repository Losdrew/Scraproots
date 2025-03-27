// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "SRObstacleCoord.generated.h"

USTRUCT(BlueprintType)
struct FObstacleCoord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Obstacle")
	int32 X;

	UPROPERTY(BlueprintReadWrite, Category = "Obstacle")
	int32 Y;

	// Default Constructor
	FObstacleCoord()
		: X(0), Y(0) {}

	// Parameterized Constructor
	FObstacleCoord(int32 InX, int32 InY)
		: X(InX), Y(InY) {}
};

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRObstacleCoord : public UObject
{
	GENERATED_BODY()

public:
	USRObstacleCoord();

	UFUNCTION(BlueprintCallable, Category = "Obstacle")
	TArray<FObstacleCoord> GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY, TArray<int32> EnemyTileIndices);

private:
	int32 GenerateObstacles(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int MinObstacles, int MaxObstacles, TArray<TArray<bool>> EnemyGrid);
	TArray<FObstacleCoord> ConvertGridToArray(const TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY);
	bool AreTilesConnected(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int32 ObstaclesTotal);
	TArray<TArray<bool>> InitializeGrid(int32 GridSizeX, int32 GridSizeY) const;
	TArray<FObstacleCoord> ConvertToCoord(TArray<int32> EnemyTileIndices);
	TArray<TArray<bool>> ConvertCoordsToGrid(int32 GridSizeX, int32 GridSizeY, TArray<FObstacleCoord> EnemyTileCoords);
};
