// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile.generated.h"

UCLASS()
class ZER0_API ACPP_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Tile();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlaceActorsInWorld(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool CastSphere(FVector DesiredSpawnLocation, float ObjectRadius);

};
