// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableWall.generated.h"

class ADropped;

UCLASS()
class BOMBERMAN2_API ABreakableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop")
	TSubclassOf<ADropped> droppedClass_;

	UFUNCTION(BlueprintCallable, Category = "Drop")
	float GetDropChance() const;

	void GeneratePossibleDrop();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walls")
	UStaticMeshComponent* wallMesh_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Walls")
	float dropChance_ = 0.2f;
};
