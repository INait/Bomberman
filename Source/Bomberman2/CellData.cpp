
#include "CellData.h"

namespace Cell
{
	void AlignWithCell(FTransform& transform)
	{
		FVector location = transform.GetLocation();
		location.X = roundf(location.X / width) * width;
		location.Y = roundf(location.Y / height) * height;

		transform.SetLocation(location);
	}

	FVector GetCellLocation(int i, int j)
	{
		return GetCellLocationWithHeight(i, j, 0.0f);
	}

	FVector GetCellLocationWithHeight(int i, int j, float z)
	{
		return FVector{ i * width, j * height, z };
	}
}
