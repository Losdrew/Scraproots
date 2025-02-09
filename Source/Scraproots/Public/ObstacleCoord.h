#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObstacleCoord.generated.h"

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
	TArray<FObstacleCoord> GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY);

private:
	TArray<TArray<bool>> CreateBoolGrid(int32 GridSizeX, int32 GridSizeY) const;
	TArray<TArray<bool>> InitializeGrid(int32 GridSizeX, int32 GridSizeY) const;
	void GenerateObstacles(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int MinObstacles, int MaxObstacles);
	TArray<FObstacleCoord> ConvertGridToArray(const TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY);
};
