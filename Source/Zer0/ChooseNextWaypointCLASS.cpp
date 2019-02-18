// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointCLASS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypointCLASS::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Grab patrol points
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();

	//using actual class instead of auto
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	//using int32 instead of auto
	//grab owner blackboard component, grab the Index which we declared in our header file, and store it inside indexfinder
	int32 IndexFinder = BlackboardComponent->GetValueAsInt(Index.SelectedKeyName);
	
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), IndexFinder)
	return EBTNodeResult::Succeeded;
}
