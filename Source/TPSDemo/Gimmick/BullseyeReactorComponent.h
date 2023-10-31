// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BullseyeReactorComponent.generated.h"


UCLASS( ClassGroup=(Custom) )
class TPSDEMO_API UBullseyeReactorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class ABullseye* TriggerSource;
	
public:	
	// Sets default values for this component's properties
	UBullseyeReactorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	virtual void Trigger() {}
		
};
