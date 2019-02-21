// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Tile.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Public/DrawDebugHelpers.h"
#include "CPP_ActorPool.h"

// Sets default values
ACPP_Tile::ACPP_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Tile::PlaceActorsInWorld(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn, float ObjectRadius, float MinScale, float MaxScale)
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool FoundLocation = GetEmptyLocation(SpawnPoint, ObjectRadius * RandomScale);
		if (FoundLocation) //is empty
			{
			float RandomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ActorToSpawn, SpawnPoint, RandomRotation, RandomScale);
			}
	//FVector RandomSpawnLocation = FMath::RandPointInBox(LevelBoundaries);
	}
}

// Called when the game starts or when spawned
void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	
	//TODO remove
	CastSphere(GetActorLocation(), 400);

	//TODO remove
	CastSphere(GetActorLocation() + FVector(0, 0, 1000), 400);
}

// Called every frame
void ACPP_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_Tile::GetEmptyLocation(FVector& OutLocation, float ObjectRadius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox LevelBoundaries(Min, Max);
	const int32 MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector DesiredSpawnLocation = FMath::RandPointInBox(LevelBoundaries);
		if(CastSphere(DesiredSpawnLocation, ObjectRadius))
		{
			OutLocation = DesiredSpawnLocation;
			return true;
		}
	}
	return false;
}

void ACPP_Tile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector DesiredSpawnPoint, float Rotation, float Scale)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	SpawnedActor->SetActorRelativeLocation(DesiredSpawnPoint);
	//this is what attaches the actors to the random location
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	//setting rotation of actor
	SpawnedActor->SetActorRotation(FRotator(0, Rotation, 0));
	//adjusting FVector of actor scale on spawn
	SpawnedActor->SetActorScale3D(FVector(Scale));
}

bool ACPP_Tile::CastSphere(FVector DesiredSpawnLocation, float ObjectRadius)
{
	FHitResult DesiredHitResult;
	//we are using position instead of vector because vector can account for many things beyond positon
	FVector GlobalLocationConversion = ActorToWorld().TransformPosition(DesiredSpawnLocation);
	bool IsCollisionDetected = GetWorld()->SweepSingleByChannel(
		DesiredHitResult,
		GlobalLocationConversion,
		GlobalLocationConversion,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // everything the camera sees / blocks the camera
		FCollisionShape::MakeSphere(ObjectRadius)
	);
	//FColor ResultColor = IsCollisionDetected ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocationConversion, 0, ObjectRadius, FQuat::Identity,  ResultColor, true, 100);
	return !IsCollisionDetected;
}

void ACPP_Tile::SetActorPool(UCPP_ActorPool* InPool)
{
	ActorPool = InPool;
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
}

