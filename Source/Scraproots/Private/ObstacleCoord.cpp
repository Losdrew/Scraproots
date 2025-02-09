#include "ObstacleCoord.h"
#include "Math/UnrealMathUtility.h"

USRObstacleCoord::USRObstacleCoord()
{
}

TArray<TArray<bool>> USRObstacleCoord::InitializeGrid(int32 GridSizeX, int32 GridSizeY) const
{
	TArray<TArray<bool>> Grid;
	Grid.SetNum(GridSizeX);
	for (int32 X = 0; X < GridSizeX; X++)
	{
		Grid[X].SetNum(GridSizeY);
		for (int32 Y = 0; Y < GridSizeY; Y++)
		{
			Grid[X][Y] = false;
		}
	}
	return Grid;
}

void USRObstacleCoord::GenerateObstacles(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int MinObstacles, int MaxObstacles)
{
	int ObstaclesTotal = 0;

	while (ObstaclesTotal < MinObstacles)
	{
		for (int32 X = 0; X < GridSizeX; X++)
		{
			for (int32 Y = 1; Y < GridSizeY; Y++)  // Start from Y = 1
			{
				int RndNum = FMath::RandRange(1, 10);
				if (RndNum == 1 && ObstaclesTotal < MaxObstacles && !Grid[X][Y])
				{
					Grid[X][Y] = true;
					ObstaclesTotal++;
				}
			}
		}
	}
}

TArray<FObstacleCoord> USRObstacleCoord::ConvertGridToArray(const TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY)
{
	TArray<FObstacleCoord> ResultArray;

	for (int32 X = 0; X < GridSizeX; X++)
	{
		for (int32 Y = 1; Y < GridSizeY; Y++)  // Start from Y = 1
		{
			if (Grid[X][Y])
			{
				ResultArray.Add(FObstacleCoord(X * 200, Y * 200));	// Store as a struct
			}
		}
	}

	return ResultArray;
}

TArray<FObstacleCoord> USRObstacleCoord::GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY)
{
	int CellsTotal = GridSizeX * GridSizeY;
	int MinObstacles = round((double)CellsTotal * 0.25);
	int MaxObstacles = round((double)CellsTotal * 0.35);

	TArray<TArray<bool>> Grid = InitializeGrid(GridSizeX, GridSizeY);

	GenerateObstacles(Grid, GridSizeX, GridSizeY, MinObstacles, MaxObstacles);

	return ConvertGridToArray(Grid, GridSizeX, GridSizeY);
}
