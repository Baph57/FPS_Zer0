// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
class ANavMeshBoundsVolume;
UCLASS()
class ZER0_API AInfiniteTerrainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
		
	//constructor
	AInfiniteTerrainGameMode();


	UFUNCTION(BlueprintCallable, Category = Custom)
	void PopulateBoundsVolumePool();


//private:
	void AddToPool(ANavMeshBoundsVolume *VolumeToAdd);

};
