// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bombMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bombMesh"));
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABomb::IsTimedOut() const
{
	return bombTimer_ >= bombTimeToBlow_;
}

void ABomb::BlowUp()
{
 // explosion
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isRemoteActivated)
	{
		bombTimer_ += DeltaTime;
	}
}

