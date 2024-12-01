#include "ObstacleCoord.h"
#include "Math/UnrealMathUtility.h"

USRObstacleCoord::USRObstacleCoord()
{
}

TArray<TArray<bool>> USRObstacleCoord::CreateBoolGrid(int32 GridSizeX, int32 GridSizeY) const
{
	TArray<TArray<bool>> Grid;

	if (GridSizeX <= 0 || GridSizeY <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid grid size! GridSizeX: %d, GridSizeY: %d"), GridSizeX, GridSizeY);
		return Grid;  // Повертаємо порожній масив
	}

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


TArray<int32> USRObstacleCoord::GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY) const
{
	int cellsTotal = GridSizeX * GridSizeY;
	int minObstacles = round((double)cellsTotal * 0.3);
	int maxObstacles = round((double)cellsTotal * 0.5);
	int obstaclesTotal = 0;

	TArray<TArray<bool>> Grid = CreateBoolGrid(GridSizeX, GridSizeY);

	while (obstaclesTotal < minObstacles)
	{
		for (int X = 0; X < GridSizeX; X++)
		{
			for (int Y = 1; Y < GridSizeY; Y++)
			{
				int rndNum = FMath::RandRange(1, 10);
				if (rndNum == 1 && obstaclesTotal < maxObstacles && !Grid[X][Y])
				{
					Grid[X][Y] = true;
					obstaclesTotal++;
				}
			}
		}
	}

	TArray<int32> ResultArray;
	for (int X = 0; X < GridSizeX; X++)
	{
		for (int Y = 0; Y < GridSizeY; Y++)
		{
			if (Grid[X][Y])
			{
				ResultArray.Add(Y + X * 1000);
			}
		}
	}

	return ResultArray;
}
