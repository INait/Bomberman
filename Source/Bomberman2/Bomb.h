// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN2_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsTimedOut() const;
	void BlowUp();

	UFUNCTION()
	int32 GetBlowRadius() const;

	UFUNCTION()
	void SetBlowRadius(int32 radius);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BombMesh")
	UStaticMeshComponent* bombMesh_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BombParams")
	float bombTimeToBlow_ = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BombParams")
	bool isRemoteActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BombParams")
	int32 blowRadius_ = 1;

private:

	float bombTimer_ = 0.0f;
};
