#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObstacleCoord.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRObstacleCoord : public UObject
{
	GENERATED_BODY()

public:
	USRObstacleCoord();

	UFUNCTION(BlueprintCallable, Category = "Obstacle")
	TArray<int32> GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY) const;

private:
	TArray<TArray<bool>> CreateBoolGrid(int32 GridSizeX, int32 GridSizeY) const;
};
