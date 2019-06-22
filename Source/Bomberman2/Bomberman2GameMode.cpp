// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2GameMode.h"
#include "Bomberman2PlayerController.h"
#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "engine/World.h"

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/GameFramework/PlayerStart.h"

#include "GameField.h"
#include "Bomb.h"
#include "CellData.h"

ABomberman2GameMode::ABomberman2GameMode()
{
}

void ABomberman2GameMode::BeginPlay()
{
	_GenerateGameField();

	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), outActors);

	// TODO: select free cells to spawn players and enemies
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
			if (auto bombermanController = CastChecked<ABomberman2PlayerController>(newPlayer))
			{
				bombermanController->SetPlayerColor();
			}
			newPlayer->GetPawn()->SetActorLocation(outActors[i]->GetActorLocation());
		}
	}

	for (int32 i = 0; i < enemiesCount_; i++)
	{
		Cell::CellIndex cell;
		cell.x = i;
		cell.y = 3;

		FTransform transform = FTransform::Identity;
		transform.SetLocation(FVector{ Cell::width * cell.x, Cell::height * cell.y, 150.0f });
		GetWorld()->SpawnActor<ACharacter>(enemyClass_, transform);
	}
}

void ABomberman2GameMode::_GenerateGameField()
{
	FTransform transform = FTransform::Identity;

	gameField_ = CastChecked<AGameField>(GetWorld()->SpawnActor<AActor>(gameFieldClass_, transform));
}

void ABomberman2GameMode::Explosion(ABomb* bomb)
{
	gameField_->Explosion(bomb->GetActorLocation(), bomb->GetBlowRadius());
}
