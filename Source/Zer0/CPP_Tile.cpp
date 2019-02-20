// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Tile.h"

// Sets default values
ACPP_Tile::ACPP_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Tile::PlaceActorsInWorld()
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox LevelBoundaries(Min, Max);
	for (size_t i = 0; i < 20.f; i++)
	{
	FVector RandomSpawnLocation = FMath::RandPointInBox(LevelBoundaries);
	UE_LOG(LogTemp, Warning, TEXT("Placem"))
	}
}

// Called when the game starts or when spawned
void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

