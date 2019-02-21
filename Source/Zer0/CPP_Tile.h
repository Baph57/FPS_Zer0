// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;

};

class UCPP_ActorPool;

UCLASS()
class ZER0_API ACPP_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Tile();


	UFUNCTION(BlueprintCallable, Category = Custom)
	void PlaceActorsInWorld(
		TSubclassOf<AActor> ActorToSpawn, 
		int32 MinSpawn = 1,
		int32 MaxSpawn = 1, 
		float ObjectRadius = 500,
		float MinScale = 1,
		float MaxScale = 1
		);

	UFUNCTION(BlueprintCallable, Category = Custom)
	void PlaceAiPawnsInWorld(
		TSubclassOf<APawn> PawnToSpawn,
		int32 MinSpawn = 1,
		int32 MaxSpawn = 1,
		float ObjectRadius = 500
		);



	TArray<FSpawnPosition> RandomizedSpawnPositions(
		const int32 &MinSpawn, 
		const int32 &MaxSpawn, 
		float MinScale, 
		float MaxScale, 
		float ObjectRadius
	);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//endgame
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	UPROPERTY(EditDefaultsOnly, Category = Custom)
		FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = Custom)
	FVector MinimumSpawningExtent;
	


	UPROPERTY(EditDefaultsOnly, Category = Custom)
		FVector MaximumSpawningExtent;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Custom)
		void SetActorPool(UCPP_ActorPool* ActorPool);


private:
	//member variable for getting empty location
	bool GetEmptyLocation(FVector& OutLocation, float ObjectRadius);

	
	void PositionNavMeshBoundsVolume();
	
	
	//The actual action of placing the actor
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, const FSpawnPosition& DesiredSpawnLocation);

	//returns a boolean value based upon whether the location is valid to spawn at or not
	bool CastSphere(FVector DesiredSpawnLocation, float ObjectRadius);

	UCPP_ActorPool* ActorPool;


	AActor* NavMeshBoundsVolume;


	void PlaceAiPawns(TSubclassOf<APawn> PawnToSpawn, const FSpawnPosition SpawnPosition);
};
