#pragma once

#include "CoreMinimal.h"
//#include "Math/UnrealMath.h"

namespace Cell
{
	struct CellIndex
	{
		int32 x;
		int32 y;
	};

	static float width = 100.0f;
	static float height = 100.0f;

	static int32 leftBorder = -5;
	static int32 rightBorder = 5;
	static int32 bottomBorder = -5;
	static int32 topBorder = 5;

	void AlignWithCell(FTransform& transform);
	FVector GetCellLocation(int32 i, int32 j);
	FVector GetCellLocationWithHeight(int32 i, int32 j, float z);

	CellIndex GetCellFromLocation(const FVector& location);

	int32 GetLinearIndex(int32 i, int32 j);
	CellIndex GetIndexFromLinear(int32 index);
};
