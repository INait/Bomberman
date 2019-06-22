// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bomberman2GameMode.generated.h"

class ABomb;
class AGameField;

UCLASS(minimalapi)
class ABomberman2GameMode : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;
public:
	ABomberman2GameMode();

	void Explosion(ABomb* bomb);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameField")
	TSubclassOf<AActor> gameFieldClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<ACharacter> enemyClass_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemies")
	int32 enemiesCount_ = 2;

private:

	UPROPERTY()
	AGameField* gameField_;

	void _GenerateGameField();
};
