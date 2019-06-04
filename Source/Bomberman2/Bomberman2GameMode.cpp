// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2GameMode.h"
#include "Bomberman2PlayerController.h"
#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "engine/World.h"

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine/Classes/GameFramework/PlayerStart.h"

#include "BreakableWall.h"
#include "UnbreakableWall.h"

#include "Bomb.h"
#include "CellData.h"

ABomberman2GameMode::ABomberman2GameMode()
{
}

void ABomberman2GameMode::Explosion(ABomb* bomb)
{
	Cell::CellIndex bombIndex = Cell::GetCellFromLocation(bomb->GetActorLocation());

	Cell::CellIndex explosionDirections[4] =
	{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

	for (Cell::CellIndex explosionCell : explosionDirections)
	{
		int32 index = Cell::GetLinearIndex(bombIndex.x + explosionCell.x, bombIndex.y + explosionCell.y);
		if(cellsContain_.Contains(index))
		{
			auto breakableWall = Cast<ABreakableWall>(cellsContain_[index]);
			if (breakableWall)
			{
				breakableWall->Destroy();
				cellsContain_.Remove(index);
			}
		}
	}
}

void ABomberman2GameMode::BeginPlay()
{
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), outActors);

	for (int32 i = 0; i < outActors.Num(); i++)
	{
		auto newPlayer = UGameplayStatics::CreatePlayer(this, i, true);
		if (!newPlayer)
		{
			// already created player controller
			newPlayer = UGameplayStatics::GetPlayerController(this, i);
		}

		if (newPlayer && newPlayer->GetPawn())
		{
			newPlayer->GetPawn()->SetActorLocation(outActors[i]->GetActorLocation());
		}
	}

	_GenerateGameField();
}

void ABomberman2GameMode::_GenerateGameField()
{
	for (auto i = Cell::leftBorder; i <= Cell::rightBorder; i++)
	{
		for (auto j = Cell::bottomBorder; j <= Cell::topBorder; j++)
		{
			int32 index = Cell::GetLinearIndex(i, j);
			freeCells_.Add(index);
		}
	}

	for (auto i = Cell::leftBorder + 1; i <= Cell::rightBorder - 1; i += 2)
	{
		for (auto j = Cell::bottomBorder + 1; j <= Cell::topBorder - 1; j += 2)
		{
			FTransform transform = FTransform::Identity;
			transform.SetLocation(FVector{ Cell::width * i, Cell::height * j, 85.0f });

			int32 index = Cell::GetLinearIndex(i, j);
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
			Cell::CellIndex cellIndex = Cell::GetIndexFromLinear(*iterator);
			transform.SetLocation(FVector{ Cell::width * cellIndex.x, Cell::height * cellIndex.y, 100.0f });
			cellsContain_.Add(*iterator, GetWorld()->SpawnActor<ABreakableWall>(breakableWallClass_, transform));

			iterator.RemoveCurrent();
		}
	}
}
