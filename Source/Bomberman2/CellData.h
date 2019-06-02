#pragma once

#include "CoreMinimal.h"
//#include "Math/UnrealMath.h"

namespace Cell
{
	static float width = 100.0f;
	static float height = 100.0f;

	static int leftBorder = -5;
	static int rightBorder = 5;
	static int bottomBorder = -5;
	static int topBorder = 5;

	void AlignWithCell(FTransform& transform);
	FVector GetCellLocation(int i, int j);
	FVector GetCellLocationWithHeight(int i, int j, float z);
};
