// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Bomberman2PlayerController.generated.h"

UCLASS()
class ABomberman2PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABomberman2PlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void DropBomb();

};


