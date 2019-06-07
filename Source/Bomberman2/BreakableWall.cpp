// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakableWall.h"

#include "Dropped.h"

#include "engine/World.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ABreakableWall::ABreakableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wallMesh"));
}

// Called when the game starts or when spawned
void ABreakableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableWall::GeneratePossibleDrop()
{
	float randomValue = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
	if (randomValue < dropBombChance_)
	{
		GetWorld()->SpawnActor<ADropped>(droppedBombClass_, GetActorTransform());
	}
	else if (randomValue < dropBombChance_ + dropBuffChance_)
	{
		GetWorld()->SpawnActor<ADropped>(droppedBuffClass_, GetActorTransform());
	}
}

