// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BullseyeEventHandler.h"
#include "DoorOpenComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSDEMO_API UDoorOpenComponent : public UBullseyeEventHandler
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Move)
	FVector MoveDistance;

	UPROPERTY(EditAnywhere, Category = Move)
	float MoveTime = 1.0f;

	FVector InitialPos;
	float AnimatingTime = 0.0f;
	
public:
	UDoorOpenComponent();

protected:
	void BeginPlay() override;

public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void Trigger() override;
};
