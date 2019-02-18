// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Zer0GameMode.h"
#include "Zer0HUD.h"
#include "Zer0Character.h"
#include "UObject/ConstructorHelpers.h"

AZer0GameMode::AZer0GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZer0HUD::StaticClass();
}
