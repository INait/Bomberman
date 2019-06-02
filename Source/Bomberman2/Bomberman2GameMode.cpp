// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2GameMode.h"
#include "Bomberman2PlayerController.h"
#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "engine/World.h"

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/GameFramework/PlayerStart.h"

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
}
