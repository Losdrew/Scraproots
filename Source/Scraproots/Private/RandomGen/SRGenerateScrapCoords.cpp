#include "RandomGen/SRGenerateScrapCoords.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Set.h"

USRGenerateScrapCoords::USRGenerateScrapCoords()
{
}

TArray<FObstacleCoord> USRGenerateScrapCoords::GenerateScrapCoords(
	int32 GridSizeXY,
	const TArray<int32>& EnemyIndices,
	const TArray<int32>& AllyIndices,
	const TArray<FObstacleCoord>& ObstacleCoords)
{
	TArray<FObstacleCoord> ScrapCoords;

	int32 ScrapCount = (GridSizeXY == 10) ? 2 : 1;

	int32 MinRow = 3;
	int32 MaxRow = 5;
	if (GridSizeXY >= 8) MaxRow = 6;
	if (GridSizeXY >= 10)
	{
		MinRow = 4;
		MaxRow = 7;
	}

	TSet<FIntPoint> Occupied;

	auto AddIndexToOccupied = [&Occupied](const TArray<int32>& Indices)
	{
		for (int32 Index : Indices)
		{
			int32 X = Index / 1000;
			int32 Y = Index % 1000;
			Occupied.Add(FIntPoint(X, Y));
		}
	};

	AddIndexToOccupied(EnemyIndices);
	AddIndexToOccupied(AllyIndices);

	for (const FObstacleCoord& Obstacle : ObstacleCoords)
	{
		int32 X = Obstacle.X / TileSize;
		int32 Y = Obstacle.Y / TileSize;
		Occupied.Add(FIntPoint(X, Y));
	}

	int Attempts = 0;
	while (ScrapCoords.Num() < ScrapCount && Attempts < 100)
	{
		int32 X = FMath::RandRange(0, GridSizeXY - 1);
		int32 Y = FMath::RandRange(MinRow, MaxRow);

		FIntPoint Candidate(X, Y);
		if (!Occupied.Contains(Candidate))
		{
			Occupied.Add(Candidate);
			ScrapCoords.Add(FObstacleCoord(X * TileSize, Y * TileSize));
		}

		Attempts++;
	}

	return ScrapCoords;
}
