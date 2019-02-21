// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile.generated.h"

class UCPP_ActorPool;

UCLASS()
class ZER0_API ACPP_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Tile();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlaceActorsInWorld(
		TSubclassOf<AActor> ActorToSpawn, 
		int32 MinSpawn = 1,
		int32 MaxSpawn = 1, 
		float ObjectRadius = 500,
		float MinScale = 1,
		float MaxScale = 1
	);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Custom)
		void SetActorPool(UCPP_ActorPool* ActorPool);

private:
	//member variable for getting empty location
	bool GetEmptyLocation(FVector& OutLocation, float ObjectRadius);

	//The actual action of placing the actor
	void PlaceActor(
		TSubclassOf<AActor> ActorToSpawn, 
		FVector DesiredSpawnPoint, 
		float Rotation,
		float Scale
	);

	//returns a boolean value based upon whether the location is valid to spawn at or not
	bool CastSphere(FVector DesiredSpawnLocation, float ObjectRadius);

	UCPP_ActorPool* ActorPool;

};
