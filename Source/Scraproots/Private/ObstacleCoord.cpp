#include "ObstacleCoord.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Queue.h"

USRObstacleCoord::USRObstacleCoord()
{
}

const int TileSize = 200;
const double MaxProbability = 0.2;
const double MinProbability = 0.25;
const double SidesProbability = 25;
const double MiddleProbability = 15;

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

int USRObstacleCoord::GenerateObstacles(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int MinObstacles, int MaxObstacles, TArray<TArray<bool>> EnemyGrid)
{
	int32 ObstaclesTotal = 0;
	Grid = InitializeGrid(GridSizeX, GridSizeY);

	while (ObstaclesTotal < MinObstacles)
	{
		for (int32 X = 0; X < GridSizeX; X++)
		{
			for (int32 Y = 1; Y < GridSizeY; Y++)  // Start from Y = 1
			{
				int RndNum = FMath::RandRange(1, 100);
				if (X > 2 && X < 2 + GridSizeX / 2 && RndNum <= 5)
				{
					if (!Grid[X][Y] && !EnemyGrid[X][Y])
					{
						Grid[X][Y] = true;
						ObstaclesTotal++;
					}
				}
				else
				{
					if ((X <= 2 || X >= 2 + GridSizeX / 2) && RndNum <= 10)
					{
						if (!Grid[X][Y] && !EnemyGrid[X][Y])
						{
							Grid[X][Y] = true;
							ObstaclesTotal++;
						}
					}
				}
			}
		}
	}
	if (AreTilesConnected(Grid, GridSizeX, GridSizeY, ObstaclesTotal))
		return ObstaclesTotal;
	else
		return -1;
}

bool USRObstacleCoord::AreTilesConnected(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int32 ObstaclesTotal)
{
	int totalEmptyCells = GridSizeX * GridSizeY - ObstaclesTotal;
	TArray<TArray<bool>> Visited = InitializeGrid(GridSizeX, GridSizeY);
	TQueue<FIntPoint> Queue;

	for (int X = 0; X < GridSizeX; X++)
	{
		for (int Y = 0; Y < GridSizeY; Y++)
		{
			if (!Grid[X][Y])
			{
				Queue.Enqueue(FIntPoint(X, Y));
				Visited[X][Y] = true;
				break;
			}
		}
		if (!Queue.IsEmpty()) break;
	}

	if (Queue.IsEmpty()) return true;

	int emptyCellsCount = 0;
	FIntPoint Directions[4] = {FIntPoint(0, 1), FIntPoint(1, 0), FIntPoint(0, -1), FIntPoint(-1, 0)};

	while (!Queue.IsEmpty())
	{
		FIntPoint Current;
		Queue.Dequeue(Current);
		emptyCellsCount++;

		for (auto& Dir : Directions)
		{
			int newX = Current.X + Dir.X;
			int newY = Current.Y + Dir.Y;
			if (newX >= 0 && newX < GridSizeX && newY >= 0 && newY < GridSizeY && !Grid[newX][newY] && !Visited[newX][newY])
			{
				Visited[newX][newY] = true;
				Queue.Enqueue(FIntPoint(newX, newY));
			}
		}
	}
	return emptyCellsCount == totalEmptyCells;
}

TArray<FObstacleCoord> USRObstacleCoord::ConvertGridToArray(const TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY)
{
	TArray<FObstacleCoord> ResultArray;

	for (int32 X = 0; X < GridSizeX; X++)
	{
		for (int32 Y = 1; Y < GridSizeY; Y++)
		{
			if (Grid[X][Y])
			{
				ResultArray.Add(FObstacleCoord(X * TileSize, Y * TileSize));
			}
		}
	}

	return ResultArray;
}

TArray<FObstacleCoord> USRObstacleCoord::ConvertToCoord(TArray<int32> EnemyTileIndices)
{
	TArray<FObstacleCoord> EnemyTileCoords;

	for (int32 Index : EnemyTileIndices)
	{
		int32 X = Index / 1000;
		int32 Y = Index % 1000;
		EnemyTileCoords.Add(FObstacleCoord(X, Y));
	}

	return EnemyTileCoords;
}

TArray<TArray<bool>> USRObstacleCoord::ConvertCoordsToGrid(int32 GridSizeX, int32 GridSizeY, TArray<FObstacleCoord> EnemyTileCoords)
{
	TArray<TArray<bool>> EnemyGrid = InitializeGrid(GridSizeX, GridSizeY);

	for (const FObstacleCoord& Coord : EnemyTileCoords)
	{
		int32 X = Coord.X;
		int32 Y = Coord.Y;

		if (X >= 0 && X < GridSizeX && Y >= 0 && Y < GridSizeY)
		{
			EnemyGrid[X][Y] = true;
		}
	}

	return EnemyGrid;
}



TArray<FObstacleCoord> USRObstacleCoord::GetRandomObstacleCoord(int32 GridSizeX, int32 GridSizeY, TArray<int32> EnemyTileIndices)
{
	int CellsTotal = GridSizeX * GridSizeY;
	int MinObstacles = round((double)CellsTotal * MinProbability);
	int MaxObstacles = round((double)CellsTotal * MaxProbability);

	TArray<TArray<bool>> Grid;
	TArray<TArray<bool>> EnemyGrid = ConvertCoordsToGrid(GridSizeX, GridSizeY, ConvertToCoord(EnemyTileIndices));

	int32 ObstaclesTotal = 0;
	do
	{
		ObstaclesTotal = GenerateObstacles(Grid, GridSizeX, GridSizeY, MinObstacles, MaxObstacles, EnemyGrid);
	} while (ObstaclesTotal == -1);

	return ConvertGridToArray(Grid, GridSizeX, GridSizeY);
}
