// Fill out your copyright notice in the Description page of Project Settings.

#include "GameField.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

#include "BreakableWall.h"
#include "UnbreakableWall.h"

// Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	floorMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	northWallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NorthWallMesh"));
	southWallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SouthWallMesh"));
	eastWallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EastWallMesh"));
	westWallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WestWallMesh"));

	floorMesh_->SetupAttachment(RootComponent);
	northWallMesh_->SetupAttachment(RootComponent);
	southWallMesh_->SetupAttachment(RootComponent);
	eastWallMesh_->SetupAttachment(RootComponent);
	westWallMesh_->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();

	_GenerateBoundsGeometry();
	_GenerateWalls();
}

void AGameField::_GenerateBoundsGeometry()
{
	floorMesh_->SetWorldScale3D(FVector{ static_cast<float>(fieldWidth_), static_cast<float>(fieldHeight_), 1.0f });

	{
		FTransform northWallTransform = FTransform::Identity;
		northWallTransform.SetLocation(FVector{ cellSize_ * fieldHeight_ / 2.0f, 0.0f, 100.0f });

		northWallMesh_->SetRelativeTransform(northWallTransform);
		northWallMesh_->SetWorldScale3D(FVector{ 0.1f, static_cast<float>(fieldHeight_), 2.0f });
	}

	{
		FTransform southWallTransform = FTransform::Identity;
		southWallTransform.SetLocation(FVector{ -cellSize_ * fieldHeight_ / 2.0f, 0.0f, 100.0f });

		southWallMesh_->SetRelativeTransform(southWallTransform);
		southWallMesh_->SetWorldScale3D(FVector{ 0.1f, static_cast<float>(fieldHeight_), 2.0f });
	}

	{
		FTransform eastWallTransform = FTransform::Identity;
		eastWallTransform.SetLocation(FVector{ 0.0f, cellSize_ * fieldWidth_ / 2.0f, 100.0f });

		eastWallMesh_->SetRelativeTransform(eastWallTransform);
		eastWallMesh_->SetWorldScale3D(FVector{ static_cast<float>(fieldWidth_), 0.1f, 2.0f });
	}

	{
		FTransform westWallTransform = FTransform::Identity;
		westWallTransform.SetLocation(FVector{ 0.0f, -cellSize_ * fieldWidth_ / 2.0f, 100.0f });

		westWallMesh_->SetRelativeTransform(westWallTransform);
		westWallMesh_->SetWorldScale3D(FVector{ static_cast<float>(fieldWidth_), 0.1f, 2.0f });
	}
}

void AGameField::_GenerateWalls()
{
	for (auto i =  -fieldWidth_ / 2; i <= fieldWidth_ / 2; i++)
	{
		for (auto j = -fieldHeight_ / 2; j <= fieldHeight_ / 2; j++)
		{
			int32 index = GetLinearIndex(i, j);
			freeCells_.Add(index);
		}
	}

	for (auto i = -fieldWidth_ / 2 + 1; i <= fieldWidth_ / 2 - 1; i += 2)
	{
		for (auto j = -fieldHeight_ / 2 + 1; j <= fieldHeight_ / 2 - 1; j += 2)
		{
			FTransform transform = FTransform::Identity;
			transform.SetLocation(FVector{ cellSize_ * i, cellSize_ * j, 100.0f });

			int32 index = GetLinearIndex(i, j);
			cellsContain_.Add(index, GetWorld()->SpawnActor<AUnbreakableWall>(unbreakableWallClass_, transform));

			freeCells_.Remove(index);
		}
	}

	for (auto iterator = freeCells_.CreateIterator(); iterator; ++iterator)
	{
		// place breakable walls
		if (UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f) < breakableWallsDensity_)
		{
			FTransform transform = FTransform::Identity;
			CellIndex cellIndex = GetIndexFromLinear(*iterator);
			transform.SetLocation(FVector{ cellSize_ * cellIndex.x, cellSize_ * cellIndex.y, 100.0f });
			cellsContain_.Add(*iterator, GetWorld()->SpawnActor<ABreakableWall>(breakableWallClass_, transform));

			iterator.RemoveCurrent();
		}
	}
}

void AGameField::Explosion(const FVector& location, int32 radius)
{
	CellIndex bombCellIndex = GetCellFromLocation(location);

	TArray<CellIndex> explosionDirections;
	for (int32 i = -radius; i <= radius; i++)
	{
		explosionDirections.Add(CellIndex{ i, 0 });
		if (i != 0)
		{
			explosionDirections.Add(CellIndex{ 0, i });
		}
	}

	for (auto it = explosionDirections.CreateConstIterator(); it; ++it)
	{
		int32 index = GetLinearIndex(bombCellIndex.x + it->x, bombCellIndex.y + it->y);
		if (cellsContain_.Contains(index))
		{
			auto breakableWall = Cast<ABreakableWall>(cellsContain_[index]);
			if (breakableWall)
			{

				breakableWall->GeneratePossibleDrop();

				breakableWall->Destroy();
				cellsContain_.Remove(index);
			}
		}
	}

	// TODO: damage characters
}

// Called every frame
void AGameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

