// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "Bomb.h"

#include "CellData.h"

ABomberman2Character::ABomberman2Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABomberman2Character::DropBombRequested()
{
	if (bombCount_ > 0)
	{
		FTransform transform = GetActorTransform();
		Cell::AlignWithCell(transform);

		auto bomb = GetWorld()->SpawnActor<ABomb>(bombClass_, transform);
		spawnedBombs_.Add(bomb);
		bombCount_--;
	}
}

void ABomberman2Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	for (auto iterator = spawnedBombs_.CreateIterator(); iterator; ++iterator)
	{
		auto bomb = *iterator;
		if (bomb->IsTimedOut())
		{
			bomb->BlowUp();
			bomb->Destroy();

			iterator.RemoveCurrent();

			bombCount_++;
		}
	}
}
