// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Tile.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Public/DrawDebugHelpers.h"
#include "CPP_ActorPool.h"
#include "NavigationSystem.h"


// Sets default values
ACPP_Tile::ACPP_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	MinimumSpawningExtent = FVector(0, -2000, 0);
	MaximumSpawningExtent = FVector(4000, 2000, 0);


}

void ACPP_Tile::SetActorPool(UCPP_ActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	ActorPool = InPool;

	PositionNavMeshBoundsVolume();
}

void ACPP_Tile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = ActorPool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CPP_Tile.cpp LINE 120|| [%s]"), *GetName())
			return;
	}

	UE_LOG(LogTemp, Warning, TEXT("CPP_Tile.cpp LINE 124|| [%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName())

	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}


template<class T>
void ACPP_Tile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float ObjectRadius, float MinScale, float MaxScale)
{

	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition DesiredSpawnPositions;
		DesiredSpawnPositions.Scale = FMath::RandRange(MinScale, MaxScale);
		bool FoundLocation = GetEmptyLocation(DesiredSpawnPositions.Location, ObjectRadius * DesiredSpawnPositions.Scale);
		if (FoundLocation) //is empty
		{
			DesiredSpawnPositions.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, DesiredSpawnPositions);

		}
	}
}

void ACPP_Tile::PlaceActorsInWorld(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float ObjectRadius, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, ObjectRadius, MinScale, MaxScale);
}

void ACPP_Tile::PlaceAiPawnsInWorld(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float ObjectRadius)
{
	RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, ObjectRadius, 1, 1);
}

void ACPP_Tile::PlaceActor(TSubclassOf<APawn> PawnToSpawn, FSpawnPosition& SpawnPosition)
{
	FRotator SpawnRotation = FRotator(0, SpawnPosition.Rotation, 0);
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnToSpawn, SpawnPosition.Location, SpawnRotation);
	if (SpawnedPawn == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Line82 || CPP_Tile.cpp || No Pawn"))
		return;
	}
	SpawnedPawn->SetActorRelativeLocation(SpawnPosition.Location);
	//this is what attaches the actors to the random location
	SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	//setting rotation of actor
	SpawnedPawn->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedPawn->SpawnDefaultController();
	SpawnedPawn->Tags.Add(FName("Enemy"));
}



// Called when the game starts or when spawned
void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_Tile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(ActorPool != nullptr && NavMeshBoundsVolume != nullptr)
	{
	ActorPool->ReturnPoolActors(NavMeshBoundsVolume);
	}
}

// Called every frame
void ACPP_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_Tile::GetEmptyLocation(FVector& OutLocation, float ObjectRadius)
{
	FBox LevelBoundaries(MinimumSpawningExtent, MaximumSpawningExtent);
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

void ACPP_Tile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FSpawnPosition& DesiredSpawnLocation) 
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	if (SpawnedActor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Line82 || CPP_Tile.cpp || No Pawn"))
			return;
	}
	SpawnedActor->SetActorRelativeLocation(DesiredSpawnLocation.Location);
	//this is what attaches the actors to the random location
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	//setting rotation of actor
	SpawnedActor->SetActorRotation(FRotator(0, DesiredSpawnLocation.Rotation, 0));
	//adjusting FVector of actor scale on spawn
	SpawnedActor->SetActorScale3D(FVector(DesiredSpawnLocation.Scale));
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




