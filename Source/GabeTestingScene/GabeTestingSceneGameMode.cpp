// Copyright Epic Games, Inc. All Rights Reserved.

#include "GabeTestingSceneGameMode.h"
#include "GabeTestingSceneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGabeTestingSceneGameMode::AGabeTestingSceneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
