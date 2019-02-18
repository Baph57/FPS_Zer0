// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuardToBeDeletedCLASS.generated.h"

/**
 * 
 */
UCLASS()
class ZER0_API APatrollingGuardToBeDeletedCLASS : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()


	UPROPERTY(EditInstanceOnly, Category = "Custom Patrol Route")
		TArray<AActor*> PatrolPointsCPP;
};
