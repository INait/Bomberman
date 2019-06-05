// Fill out your copyright notice in the Description page of Project Settings.

#include "Dropped.h"

// Sets default values
ADropped::ADropped()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	dropMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("dropMesh"));
}

// Called when the game starts or when spawned
void ADropped::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropped::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

