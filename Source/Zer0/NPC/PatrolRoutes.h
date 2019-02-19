// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoutes.generated.h"



//Actor component that helps Ai choose the next patrol waypoint
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZER0_API UPatrolRoutes : public UActorComponent
{
	GENERATED_BODY()

public:
	//getter
	TArray<AActor*> GetPatrolPoints() const;


private:

	UPROPERTY(EditInstanceOnly, Category = "Custom Patrol Route")
		TArray<AActor*> PatrolPoints;
};

