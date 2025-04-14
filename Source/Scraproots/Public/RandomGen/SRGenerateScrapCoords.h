#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomGen/SRObstacleCoord.h"
#include "SRGenerateScrapCoords.generated.h"

UCLASS()
class SCRAPROOTS_API USRGenerateScrapCoords : public UObject
{
	GENERATED_BODY()

public:
	USRGenerateScrapCoords();

	UFUNCTION(BlueprintCallable, Category = "Random Generation")
	static TArray<FObstacleCoord> GenerateScrapCoords(
		int32 GridSizeXY,
		const TArray<int32>& EnemyIndices,
		const TArray<int32>& AllyIndices,
		const TArray<FObstacleCoord>& ObstacleCoords);
};
