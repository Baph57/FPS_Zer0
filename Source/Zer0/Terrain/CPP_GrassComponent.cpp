// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_GrassComponent.h"


// Sets default values for this component's properties
UCPP_GrassComponent::UCPP_GrassComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_GrassComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnGrass();
}

void UCPP_GrassComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnCount; i++)
	{
		FVector Location = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(Location));
	}
}

// Called every frame
void UCPP_GrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
