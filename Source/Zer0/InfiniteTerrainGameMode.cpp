// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "Zer0HUD.h"
#include "Player/PlayerZer0.h"
#include "UObject/ConstructorHelpers.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZer0HUD::StaticClass();
}
