// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypointCLASS.generated.h"

/**
 * 
 */
UCLASS()
class ZER0_API UChooseNextWaypointCLASS : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	///publically exposing a Blackboard Key Struct
	//creates a new key in blackboard called "Index"
	UPROPERTY(EditAnywhere, Category = "Custom Blackboard")
		struct FBlackboardKeySelector Index;
};
