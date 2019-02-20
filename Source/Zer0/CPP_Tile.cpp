// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Tile.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Public/DrawDebugHelpers.h"

// Sets default values
ACPP_Tile::ACPP_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Tile::PlaceActorsInWorld(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox LevelBoundaries(Min, Max);
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
	FVector RandomSpawnLocation = FMath::RandPointInBox(LevelBoundaries);
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	SpawnedActor->SetActorRelativeLocation(RandomSpawnLocation);
	//this is what attaches the actors to the random location
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	
	//example confirmed spherecast hit
	CastSphere(GetActorLocation(), 400);

	//example sphere cast clear
	CastSphere(GetActorLocation() + FVector(0, 0, 1000), 400);
}

// Called every frame
void ACPP_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_Tile::CastSphere(FVector DesiredSpawnLocation, float ObjectRadius)
{
	FHitResult DesiredHitResult;
	bool IsCollisionDetected = GetWorld()->SweepSingleByChannel(
		DesiredHitResult,
		DesiredSpawnLocation,
		DesiredSpawnLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_Camera, // everything the camera sees / blocks the camera
		FCollisionShape::MakeSphere(ObjectRadius)
	);
	FColor ResultColor = IsCollisionDetected ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), DesiredSpawnLocation, ObjectRadius, 100, ResultColor, true, 100);
	return IsCollisionDetected;
}

