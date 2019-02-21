// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "Engine/World.h"

void ACPP_InfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	//same thing as below
	///TActorIterator/*<ANavMeshBoundsVolume> */VolumeIterator(GetWorld())
	
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void ACPP_InfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found actor %s"), *VolumeToAdd->GetName());

}