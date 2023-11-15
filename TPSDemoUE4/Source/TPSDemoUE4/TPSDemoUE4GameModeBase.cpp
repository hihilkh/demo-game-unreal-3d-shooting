// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSDemoUE4GameModeBase.h"

void ATPSDemoUE4GameModeBase::GameOver()
{
	GameOverDelegate.Broadcast();
}
