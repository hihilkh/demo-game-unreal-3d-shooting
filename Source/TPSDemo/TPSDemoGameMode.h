// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSDemoGameMode.generated.h"

UCLASS(minimalapi)
class ATPSDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

	UPROPERTY(BlueprintAssignable, Category = Event)
	FGameOverDelegate GameOverDelegate;
	
public:
	ATPSDemoGameMode();

public:

	UFUNCTION(BlueprintCallable)
	void GameOver();
};



