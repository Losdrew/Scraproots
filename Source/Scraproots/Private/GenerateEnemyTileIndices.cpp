// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateEnemyTileIndices.h"

USRGenerateEnemyTileIndices::USRGenerateEnemyTileIndices()
{
}

TArray<int32> USRGenerateEnemyTileIndices::GenerateEnemyTileIndices(int32 NumberOfUnits, int32 GridSize)
{
	TArray<int32> RandomEnemyIndices;
	TSet<int32> UsedIndices;	  

	while (RandomEnemyIndices.Num() < NumberOfUnits)
	{
		int32 Y = FMath::RandRange(0, GridSize - 1);			   // Випадковий Y у межах сітки
		int32 X = FMath::RandRange(GridSize / 2, GridSize - 1);  // Випадковий X у верхній половині сітки

		int32 CellIndex = X + Y * 1000;

		if (!UsedIndices.Contains(CellIndex))  // Перевіряємо, чи клітинка не зайнята
		{
			UsedIndices.Add(CellIndex);
			RandomEnemyIndices.Add(CellIndex);
		}
	}

	return RandomEnemyIndices;
}
