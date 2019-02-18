// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypointCLASS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuardToBeDeletedCLASS.h" //TODO guess what? DE-LETE THIS
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypointCLASS::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	///Getting our patrol points
	//Grab the AI owner of the controller
	AAIController* AIController = OwnerComp.GetAIOwner();

	//Grabbing the pawn the controller is controlling
	APawn* ControlledPawn = AIController->GetPawn();

	//casting this functionality to our patrolling guard class, which restrains this function
	//to only work on the patrolling guard class AT THE MOMENT
	APatrollingGuardToBeDeletedCLASS* PatrollingGuard = Cast<APatrollingGuardToBeDeletedCLASS>(ControlledPawn);

	//patrol points is now a TArray that contains the 'actor' target points which are our patrol points!
	TArray<AActor*> PatrolPoints = PatrollingGuard->PatrolPointsCPP;


	///Setting our next waypoint || DOES NOT increment value
	//Grabbing the owning component and getting the blackboard component from it 
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	//grab owner blackboard component, grab the Index which we declared in our header file, and store it inside indexfinder
	int32 IndexFinder = BlackboardComponent->GetValueAsInt(Index.SelectedKeyName);
	
	//Going into our Blackboard component and using our UPROPERTY's selected key name, we set the value
	//of the next index to whatever our IndexFinder is, this DOES NOT increment the value
	BlackboardComponent->SetValueAsObject(WaypointIndex.SelectedKeyName, PatrolPoints[IndexFinder]);



	///Increment our index
	//grabbing our iterator, adding one, and using modulus to return remainder against the 
	//length of our patrol points (PatrolPoints.Num())
	int32 NextIndex = (IndexFinder + 1) % PatrolPoints.Num();

	//taking our same blackboard component and setting the value of Index to the value of NextIndex
	//effectively iterating through our array and setting a patrol path in C++!
	BlackboardComponent->SetValueAsInt(Index.SelectedKeyName, NextIndex);








	//TODO protect against empty patrol routes


	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), IndexFinder)
	return EBTNodeResult::Succeeded;
}
