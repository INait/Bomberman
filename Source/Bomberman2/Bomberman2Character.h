// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomberman2Character.generated.h"

class ABomb;
class UPointLightComponent;

UCLASS(Blueprintable)
class ABomberman2Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABomberman2Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void DropBombRequested();

	void SetCharacterColor(const FLinearColor& color);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLight")
	UPointLightComponent* playerLight_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
	int32 bombCount_ = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
	int32 bombBlowRadius_ = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bomb")
	TSubclassOf<ABomb> bombClass_;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

private:

	TSet<ABomb*> spawnedBombs_;
};

