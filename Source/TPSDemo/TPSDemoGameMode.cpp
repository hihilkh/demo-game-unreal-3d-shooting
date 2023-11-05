// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSDemoGameMode.h"
#include "ThirdPerson/ThirdPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPSDemoGameMode::ATPSDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATPSDemoGameMode::GameOver()
{
	GameOverDelegate.Broadcast();
}
