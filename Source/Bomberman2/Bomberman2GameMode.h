// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bomberman2GameMode.generated.h"

class ABomb;
class ABreakableWall;
class AUnbreakableWall;

UCLASS(minimalapi)
class ABomberman2GameMode : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;
public:
	ABomberman2GameMode();

	void Explosion(ABomb* bomb);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	TSubclassOf<AUnbreakableWall> unbreakableWallClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	TSubclassOf<ABreakableWall> breakableWallClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	float breakableWallsDensity_ = 0.3f;

private:

	void _GenerateGameField();

	TSet<int32> freeCells_;
	TMap<int32, AActor*> cellsContain_;
};
