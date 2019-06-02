// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomberman2Character.generated.h"

UCLASS(Blueprintable)
class ABomberman2Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABomberman2Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

};

