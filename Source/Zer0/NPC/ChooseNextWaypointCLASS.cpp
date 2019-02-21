// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointCLASS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoutes.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypointCLASS::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	//TODO protect against empty patrol routes AND no Patrol Route Component
	


	///Getting our patrol points
	//Grab the AI owner of the controller & 
	//Grabbing the pawn the controller is controlling
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	//Taking our controlled pawn and finding our patrol routes component
	UPatrolRoutes* PatrolRoutes = ControlledPawn->FindComponentByClass<UPatrolRoutes>();

	//protecting against PatrolRoutes = nullptr;
	if (!ensure(PatrolRoutes)) { return EBTNodeResult::Failed; }

	//going into our patrol routes component and grabbing the getter
	auto PatrolledPoints = PatrolRoutes->GetPatrolPoints();

	if (PatrolledPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points! ChooseNextWaypointCLASS Line 31"))
	}


	///Setting our next waypoint || DOES NOT increment value
	//Grabbing the owning component and getting the blackboard component from it 
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	//grab owner blackboard component, grab the Index which we declared in our header file, and store it inside indexfinder
	int32 IndexFinder = BlackboardComponent->GetValueAsInt(Index.SelectedKeyName);
	
	//Going into our Blackboard component and using our UPROPERTY's selected key name, we set the value
	//of the next index to whatever our IndexFinder is, this DOES NOT increment the value
	BlackboardComponent->SetValueAsObject(WaypointIndex.SelectedKeyName, PatrolledPoints[IndexFinder]);



	///Increment our index
	//grabbing our iterator, adding one, and using modulus to return remainder against the 
	//length of our patrol points (PatrolPoints.Num())
	int32 NextIndex = (IndexFinder + 1) % PatrolledPoints.Num();

	//taking our same blackboard component and setting the value of Index to the value of NextIndex
	//effectively iterating through our array and setting a patrol path in C++!
	BlackboardComponent->SetValueAsInt(Index.SelectedKeyName, NextIndex);











	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), IndexFinder)
	return EBTNodeResult::Succeeded;
}
