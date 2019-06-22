// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Bomberman2Character.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"

ABomberman2PlayerController::ABomberman2PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABomberman2PlayerController::SetPlayerColor()
{
	auto characterPawn = CastChecked<ABomberman2Character>(GetPawn());
	if (!characterPawn)
	{
		return;
	}

	auto id = GetLocalPlayer()->GetControllerId();
	if (id == 0)
	{
		characterPawn->SetCharacterColor(FLinearColor::Blue);
	}
	else if (id == 1)
	{
		characterPawn->SetCharacterColor(FLinearColor::Green);
	}
}

void ABomberman2PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABomberman2PlayerController::MoveForward(float AxisValue)
{
	if (auto pawn = GetPawn())
	{
		const FVector Direction = FVector{ 1.0f, 0.0f, 0.0f };
		pawn->AddMovementInput(Direction, AxisValue);
	}
}

void ABomberman2PlayerController::MoveRight(float AxisValue)
{
	if (auto pawn = GetPawn())
	{
		const FVector Direction = FVector{ 0.0f, 1.0f, 0.0f };
		pawn->AddMovementInput(Direction, AxisValue);
	}
}

void ABomberman2PlayerController::DropBomb()
{
	auto characterPawn = CastChecked<ABomberman2Character>(GetPawn());
	if (characterPawn)
	{
		characterPawn->DropBombRequested();
	}
}

void ABomberman2PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	auto id = GetLocalPlayer()->GetControllerId();
	if (id == 0)
	{
		InputComponent->BindAxis("MoveForward_P1", this, &ABomberman2PlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P1", this, &ABomberman2PlayerController::MoveRight);
		InputComponent->BindAction("DropBomb_P1", IE_Pressed, this, &ABomberman2PlayerController::DropBomb);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveForward_P2", this, &ABomberman2PlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P2", this, &ABomberman2PlayerController::MoveRight);
		InputComponent->BindAction("DropBomb_P2", IE_Pressed, this, &ABomberman2PlayerController::DropBomb);
	}
}
