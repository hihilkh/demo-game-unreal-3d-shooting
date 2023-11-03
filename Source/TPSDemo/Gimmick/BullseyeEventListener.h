// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BullseyeEventListener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSDEMO_API UBullseyeEventListener : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString EventName = FString(TEXT(""));

	/** Eventを何回TriggerしたらHandlerのTrigger関数を呼び出すか */
	UPROPERTY(EditAnywhere)
	int CountToTrigger = 1;

	int TriggerCount = 0;
	class UBullseyeEventHandler* EventHandler;

public:	
	// Sets default values for this component's properties
	UBullseyeEventListener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void Trigger(const FString& Name);

	UFUNCTION()
	void TriggerFail(const FString& Name);
};
