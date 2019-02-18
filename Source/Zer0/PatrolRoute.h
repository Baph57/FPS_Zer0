// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

UCLASS()
class ZER0_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:
	//getter
	TArray<AActor*> GetPatrolPoints() const;


private:

	UPROPERTY(EditInstanceOnly, Category = "Custom Patrol Route")
		TArray<AActor*> PatrolPoints;

};
