// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2GameMode.h"
#include "Bomberman2PlayerController.h"
#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "engine/World.h"

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/GameFramework/PlayerStart.h"

#include "BreakableWall.h"
#include "UnbreakableWall.h"

namespace Cell
{
	float width = 100.0f;
	float height = 100.0f;

	int32 leftBorder = -5;
	int32 rightBorder = 5;
	int32 bottomBorder = -5;
	int32 topBorder = 5;
};

ABomberman2GameMode::ABomberman2GameMode()
{
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

	for (auto i = Cell::leftBorder + 1; i <= Cell::rightBorder - 1; i += 2)
	{
		for (auto j = Cell::bottomBorder + 1; j <= Cell::topBorder - 1; j += 2)
		{
			FTransform transform = FTransform::Identity;
			transform.SetLocation(FVector{ Cell::width * i, Cell::height * j, 85.0f });

			GetWorld()->SpawnActor<AUnbreakableWall>(unbreakableWallClass_, transform);
		}
	}


	FTransform transform = FTransform::Identity;
	transform.SetLocation(FVector{ 100.0f, 100.0f, 100.0f });
	GetWorld()->SpawnActor<ABreakableWall>(breakableWallClass_, transform);

	transform.SetLocation(FVector{ 100.0f, 200.0f, 100.0f });
	GetWorld()->SpawnActor<ABreakableWall>(breakableWallClass_, transform);

	transform.SetLocation(FVector{ 100.0f, 300.0f, 100.0f });
	GetWorld()->SpawnActor<ABreakableWall>(breakableWallClass_, transform);
}
