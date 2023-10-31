// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BullseyeReactorComponent.h"
#include "BullseyeMoveReactorComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSDEMO_API UBullseyeMoveReactorComponent : public UBullseyeReactorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Move)
	FVector MoveDistance;

	UPROPERTY(EditAnywhere, Category = Move)
	float MoveTime;

	FVector InitialPos;
	float AnimatingTime = 0.0f;
	
public:
	UBullseyeMoveReactorComponent();

protected:
	void BeginPlay() override;

public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void Trigger() override;
};
