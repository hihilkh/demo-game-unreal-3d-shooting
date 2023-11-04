// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BullseyeEmitter.generated.h"

UCLASS()
class TPSDEMO_API ABullseyeEmitter : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggeredDelegate, ABullseyeEmitter*, Sender);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerFailedDelegate, ABullseyeEmitter*, Sender);

	UPROPERTY(EditAnywhere, Category = Emission)
	TSubclassOf<class ABullseye> BullseyeClass;

	UPROPERTY(EditAnywhere, Category = Emission)
	TArray<FVector> EmitVelocityArray;

	/** 負数：時間制限がない */
	UPROPERTY(EditAnywhere, Category = Emission)
	float TriggerFailedTime = -1.0f;

	/** TriggeredDelegateを2回以上Broadcastできるか */
	UPROPERTY(EditAnywhere, Category = Event)
	bool bCanReuse = false;
	
	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggeredDelegate TriggeredDelegate;

	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggerFailedDelegate TriggerFailedDelegate;

	TArray<class ABullseye*> EmittedBullseyeArray;
	bool bEmitting = false;
	float EmittingAcumulatedTime = 0.0f;
	
public:	
	// Sets default values for this actor's properties
	ABullseyeEmitter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Emit();
	
	UFUNCTION(BlueprintCallable)
	void ReInit();

private:
	void Trigger(bool bDestroy);
	void TriggerFail();

	UFUNCTION()
	void BullseyeTriggeredHandler(ABullseye* Sender);
};
