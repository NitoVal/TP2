// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP2GameMode.h"
#include "TP2Character.h"
#include "UObject/ConstructorHelpers.h"

ATP2GameMode::ATP2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
