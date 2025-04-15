#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomGen/SRObstacleCoord.h"
#include "SRGenerateScrapCoords.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SCRAPROOTS_API USRGenerateScrapCoords : public UObject
{
	GENERATED_BODY()

public:
	USRGenerateScrapCoords();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
	int32 TileSize = 200;

	UFUNCTION(BlueprintCallable, Category = "Random Generation")
	TArray<FObstacleCoord> GenerateScrapCoords(
		int32 GridSizeXY,
		const TArray<int32>& EnemyIndices,
		const TArray<int32>& AllyIndices,
		const TArray<FObstacleCoord>& ObstacleCoords);
};
