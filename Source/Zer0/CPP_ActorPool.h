// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZER0_API UCPP_ActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_ActorPool();

	AActor* Checkout(); //state of pool?
	void ReturnPoolActors(AActor* ActorToReturn);
	void AddPoolActors(AActor* ActorToAdd);


private:
	TArray<AActor*>ActorPool;
};
