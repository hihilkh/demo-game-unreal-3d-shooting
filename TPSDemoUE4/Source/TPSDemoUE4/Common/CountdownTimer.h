// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CountdownTimer.generated.h"

UCLASS()
class TPSDEMOUE4_API ACountdownTimer : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeUpDelegate, ACountdownTimer*, Sender);

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTimeUpDelegate TimeUpDelegate;
	
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> DisplayUIClass;

	UPROPERTY(BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUserWidget* DisplayUI;
	
	UPROPERTY(VisibleAnywhere, Category = Timer, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RemainingTime = 0.0f;

	bool bCountingDown = false;
	
public:	
	// Sets default values for this actor's properties
	ACountdownTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FTimeUpDelegate& OnTimeUp() { return TimeUpDelegate; }
	
	UFUNCTION(BlueprintCallable)
	void StartCountdown(float TotalTime);

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetCountingDown() const { return bCountingDown; }
};
