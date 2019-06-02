// Fill out your copyright notice in the Description page of Project Settings.

#include "UnbreakableWall.h"

// Sets default values
AUnbreakableWall::AUnbreakableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wallMesh"));
}

// Called when the game starts or when spawned
void AUnbreakableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnbreakableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

