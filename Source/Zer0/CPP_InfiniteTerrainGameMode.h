// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zer0GameMode.h"
#include "CPP_InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZER0_API ACPP_InfiniteTerrainGameMode : public AZer0GameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void PopulateBoundsVolumePool();

private:

	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
