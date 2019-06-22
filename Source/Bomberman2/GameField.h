// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"

class UStaticMeshComponent;
class AUnbreakableWall;
class ABreakableWall;

UCLASS()
class BOMBERMAN2_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();

	void Explosion(const FVector& location, int32 radius);

private:
	void _GenerateBoundsGeometry();
	void _GenerateWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	struct CellIndex
	{
		int32 x; // height
		int32 y; // width
	};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetLinearIndex(int32 i, int32 j)
	{
		return (i + fieldWidth_ / 2) + fieldWidth_ * (j + fieldHeight_ / 2);
	}

	CellIndex GetIndexFromLinear(int32 index)
	{
		CellIndex cellIndex;
		cellIndex.x = index % fieldWidth_ - fieldWidth_ / 2;
		cellIndex.y = index / fieldWidth_ - fieldHeight_ / 2;
		return cellIndex;
	}

	CellIndex GetCellFromLocation(const FVector& location)
	{
		CellIndex cellIndex;
		cellIndex.x = static_cast<int32>(roundf(location.X / cellSize_));
		cellIndex.y = static_cast<int32>(roundf(location.Y / cellSize_));

		return cellIndex;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* floorMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* northWallMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* southWallMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* eastWallMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Geometry")
	UStaticMeshComponent* westWallMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	TSubclassOf<AUnbreakableWall> unbreakableWallClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	TSubclassOf<ABreakableWall> breakableWallClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	float breakableWallsDensity_ = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cells")
	int32 fieldWidth_ = 11;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cells")
	int32 fieldHeight_ = 11;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cells")
	float cellSize_ = 100.0f;

	TSet<int32> freeCells_;
	TMap<int32, AActor*> cellsContain_;
};
