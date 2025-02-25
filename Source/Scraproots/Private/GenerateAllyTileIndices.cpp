// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateAllyTileIndices.h"
#include "Math/UnrealMathUtility.h"

USRGenerateAllyTileIndices::USRGenerateAllyTileIndices()
{
}

TArray<int32> USRGenerateAllyTileIndices::GenerateAllyTileIndices(int32 NumberOfUnits, int32 GridYSize)
{
	TArray<int32> PossibleIndices;
	TArray<int32> RandomAllyIndices;

	// ���������� PossibleNumbers ������� �� 0 �� M
	for (int32 i = 0; i < GridYSize; i++)
	{
		PossibleIndices.Add(i);
	}

	// ��������� PossibleNumbers (Fisher-Yates Shuffle)
	for (int32 i = PossibleIndices.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::RandRange(0, i);
		PossibleIndices.Swap(i, j);
	}

	// ������ ����� N ��������� �������� � RandomNumbers
	for (int32 i = 0; i < NumberOfUnits && i < PossibleIndices.Num(); i++)
	{
		RandomAllyIndices.Add(PossibleIndices[i] * 1000);
	}

	return RandomAllyIndices;
}
