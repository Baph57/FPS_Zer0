// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Zer0GameMode.h"
#include "Zer0HUD.h"
#include "Player/PlayerZer0.h"
#include "UObject/ConstructorHelpers.h"

AZer0GameMode::AZer0GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZer0HUD::StaticClass();
}
