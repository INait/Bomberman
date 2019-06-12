// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

#include "Dropped.h"
#include "Bomb.h"

#include "CellData.h"

ABomberman2Character::ABomberman2Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABomberman2Character::BeginOverlap);

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

	playerLight_ = CreateDefaultSubobject<UPointLightComponent>(TEXT("PlayerLight"));
	playerLight_->SetupAttachment(RootComponent);
}

void ABomberman2Character::DropBombRequested()
{
	if (bombCount_ > 0)
	{
		FTransform transform = GetActorTransform();
		Cell::AlignWithCell(transform);

		auto bomb = GetWorld()->SpawnActor<ABomb>(bombClass_, transform);
		bomb->SetBlowRadius(bombBlowRadius_);
		spawnedBombs_.Add(bomb);
		bombCount_--;
	}
}

void ABomberman2Character::SetCharacterColor(const FLinearColor& color)
{
	if (playerLight_)
	{
		playerLight_->SetLightColor(color);
	}
}

void ABomberman2Character::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ADropped* dropped = CastChecked<ADropped>(OtherActor);
	if (dropped)
	{
		if (dropped->GetClass()->GetName() == L"DroppedBomb_C")
		{
			bombCount_++;
		}
		else if (dropped->GetClass()->GetName() == L"DroppedBuff_C")
		{
			bombBlowRadius_++;
		}

		dropped->Destroy();
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

			if (bombCount_ == 0)
			{
				bombCount_++;
			}

			if (bombBlowRadius_ > 1)
			{
				bombBlowRadius_--;
			}
		}
	}
}
