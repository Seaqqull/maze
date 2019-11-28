// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MDGenGameMode.h"
#include "MDGen.h"
#include "MDGenCharacter.h"

AMDGenGameMode::AMDGenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GeneralContent/Character/BluePrint/B_FemaleCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
