#include "ObstacleCoord.h"
#include "Math/UnrealMathUtility.h"

USRObstacleCoord::USRObstacleCoord()
{
}

const int TileSize = 200;
const double MinProbability = 0.25;
const double MaxProbability = 0.35;

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
				int RndNum = FMath::RandRange(1, 10);
				if (RndNum == 1 && ObstaclesTotal < MaxObstacles && !Grid[X][Y] && !EnemyGrid[X][Y])
				{
					Grid[X][Y] = true;
					ObstaclesTotal++;
				}
			}
		}
	}
	if (AreTilesConnected(Grid, GridSizeX, GridSizeY, ObstaclesTotal))
		return ObstaclesTotal;
	else
		return -1;
}

#include "ObstacleCoord.h"
#include "Containers/Queue.h"

bool USRObstacleCoord::AreTilesConnected(TArray<TArray<bool>>& Grid, int32 GridSizeX, int32 GridSizeY, int32 ObstaclesTotal)
{
	// «найдемо першу порожню кл≥тинку дл€ старту
	int32 StartX = -1, StartY = -1;
	for (int32 X = 0; X < GridSizeX; X++)
	{
		for (int32 Y = 0; Y < GridSizeY; Y++)
		{
			if (!Grid[X][Y])  // якщо це порожн€ кл≥тинка
			{
				StartX = X;
				StartY = Y;
				break;
			}
		}
		if (StartX != -1) break;
	}

	// якщо немаЇ жодноњ порожньоњ кл≥тинки, вважаЇмо, що вони "з'Їднан≥"
	if (StartX == -1) return true;

	// —творимо коп≥ю дл€ перев≥рки в≥дв≥даних кл≥тинок
	TArray<TArray<bool>> Visited = InitializeGrid(GridSizeX, GridSizeY);

	// ¬икористаЇмо BFS дл€ пошуку вс≥х з'Їднаних порожн≥х кл≥тинок
	TQueue<FIntPoint> Queue;
	Queue.Enqueue(FIntPoint(StartX, StartY));
	Visited[StartX][StartY] = true;

	const int32 Directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int32 EmptyCellsCount = 1;
	int32 TotalEmptyCells = GridSizeX * GridSizeY - ObstaclesTotal;

	while (!Queue.IsEmpty())
	{
		FIntPoint Current;
		Queue.Dequeue(Current);

		for (const auto& Dir : Directions)
		{
			int32 NewX = Current.X + Dir[0];
			int32 NewY = Current.Y + Dir[1];

			if (NewX >= 0 && NewX < GridSizeX && NewY >= 0 && NewY < GridSizeY &&
				!Grid[NewX][NewY] && !Visited[NewX][NewY])
			{
				Visited[NewX][NewY] = true;
				Queue.Enqueue(FIntPoint(NewX, NewY));
				EmptyCellsCount++;
			}
		}
	}

	// якщо к≥льк≥сть в≥дв≥даних порожн≥х кл≥тинок сп≥впадаЇ з загальною к≥льк≥стю Ч значить, вони вс≥ з'Їднан≥
	return EmptyCellsCount == TotalEmptyCells;
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
