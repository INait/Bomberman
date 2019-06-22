
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

	CellIndex GetCellFromLocation(const FVector& location)
	{
		CellIndex cellIndex;
		cellIndex.x = static_cast<int32>(roundf(location.X / width));
		cellIndex.y = static_cast<int32>(roundf(location.Y / height));

		return cellIndex;
	}

	FVector GetCellLocation(int32 i, int32 j)
	{
		return GetCellLocationWithHeight(i, j, 0.0f);
	}

	FVector GetCellLocationWithHeight(int32 i, int32 j, float z)
	{
		return FVector{ i * width, j * height, z };
	}

	int32 GetLinearIndex(int32 i, int32 j)
	{
		return (i - leftBorder)  + (rightBorder - leftBorder + 1) * (j - bottomBorder);
	}

	CellIndex GetIndexFromLinear(int32 index)
	{
		CellIndex cellIndex;
		cellIndex.x = index % (rightBorder - leftBorder + 1) + leftBorder;
		cellIndex.y = index / (rightBorder - leftBorder + 1) + bottomBorder;
		return cellIndex;
	}
}
