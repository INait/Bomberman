// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Bomberman2PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Bomberman2Character.h"
#include "Engine/World.h"

ABomberman2PlayerController::ABomberman2PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABomberman2PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABomberman2PlayerController::MoveForward(float AxisValue)
{
	auto pawn = GetPawn();
	check(pawn);

	const FVector Direction = FVector{ 1.0f, 0.0f, 0.0f };
	pawn->AddMovementInput(Direction, AxisValue);
}

void ABomberman2PlayerController::MoveRight(float AxisValue)
{
	auto pawn = GetPawn();
	check(pawn);

	const FVector Direction = FVector{ 0.0f, 1.0f, 0.0f };
	pawn->AddMovementInput(Direction, AxisValue);
}

void ABomberman2PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABomberman2PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABomberman2PlayerController::MoveRight);
}
