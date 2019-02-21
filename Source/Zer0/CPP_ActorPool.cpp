// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ActorPool.h"

// Sets default values for this component's properties
UCPP_ActorPool::UCPP_ActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UCPP_ActorPool::Checkout()
{
	if (ensure(ActorPool.Num() == 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("error line 19 ActorPool"), *GetName());
		return nullptr;
	}
	return ActorPool.Pop();
}

void UCPP_ActorPool::ReturnPoolActors(AActor * ActorToReturn)
{
	if (ensure(ActorToReturn == nullptr)) 
	{
	UE_LOG(LogTemp, Error, TEXT("[%s] Actor Returned: null."), *GetName())
	}
	else
	{
		AddPoolActors(ActorToReturn);
	}

}

void UCPP_ActorPool::AddPoolActors(AActor * ActorToAdd)
{
	if (ensure(ActorToAdd == nullptr)) 
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] added null actor"), *GetName())
			return;
	}
	ActorPool.Push(ActorToAdd);


	ReturnPoolActors(ActorToAdd);
}
