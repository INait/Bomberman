// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dropped.generated.h"

UCLASS()
class BOMBERMAN2_API ADropped : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropped();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	UStaticMeshComponent* dropMesh_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
