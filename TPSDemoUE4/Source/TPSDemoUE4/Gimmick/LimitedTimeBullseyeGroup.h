// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LimitedTimeBullseyeGroup.generated.h"

UCLASS()
class TPSDEMOUE4_API ALimitedTimeBullseyeGroup : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggeredDelegate, ALimitedTimeBullseyeGroup*, Sender);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerFailedDelegate, ALimitedTimeBullseyeGroup*, Sender);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bullseye, meta = (AllowPrivateAccess = "true"))
	TArray<class ABullseye*> BullseyeArray;

	UPROPERTY(EditAnywhere, Category = Timer)
	float TimeLimit;

	UPROPERTY(EditAnywhere, Category = Timer)
	TSubclassOf<class ACountdownTimer> TimerClass;

	ACountdownTimer* Timer;

	UPROPERTY(EditAnywhere, Category = Timer)
	float ResetWaitTime = 2.0f;

	float CurrentResetWaitingTime = 0.0f;
	
	UPROPERTY(VisibleAnywhere)
	int CurrentTriggeredBullseyeCount = 0;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggeredDelegate TriggeredDelegate;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggerFailedDelegate TriggerFailedDelegate;
	
public:	
	// Sets default values for this actor's properties
	ALimitedTimeBullseyeGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void StartCountdown();
	
private:

	void SetAllBullseyeActive(bool bActive);

	void Trigger();
	void TriggerFail();

	UFUNCTION()
	void TimerUpHandler(ACountdownTimer* Sender);
	
	UFUNCTION()
	void BullseyeTriggeredHandler(ABullseye* Sender);
};
