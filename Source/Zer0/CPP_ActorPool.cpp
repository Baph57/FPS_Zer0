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
	return nullptr;
}

void UCPP_ActorPool::ReturnPoolActors(AActor * ActorToReturn)
{

}

void UCPP_ActorPool::AddPoolActors(AActor * ActorToAdd)
{

}
