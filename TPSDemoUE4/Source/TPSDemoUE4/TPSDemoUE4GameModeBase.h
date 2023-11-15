// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSDemoUE4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSDEMOUE4_API ATPSDemoUE4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

	UPROPERTY(BlueprintAssignable, Category = Event)
	FGameOverDelegate GameOverDelegate;
	
public:

	UFUNCTION(BlueprintCallable)
	void GameOver();
};
