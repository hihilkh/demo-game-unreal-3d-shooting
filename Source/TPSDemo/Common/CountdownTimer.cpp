// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownTimer.h"

#include "Blueprint/UserWidget.h"

// Sets default values
ACountdownTimer::ACountdownTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACountdownTimer::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}

void ACountdownTimer::BeginDestroy()
{
	if (DisplayUI)
	{
		DisplayUI->RemoveFromParent();
		DisplayUI = nullptr;
	}
	
	Super::BeginDestroy();
}

// Called every frame
void ACountdownTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RemainingTime -= DeltaTime;
	if (RemainingTime < 0.0f)
	{
		RemainingTime = 0.0f;
		TimeUpDelegate.Broadcast(this);
		bCountingDown = false;
		SetActorTickEnabled(false);
	}
}

void ACountdownTimer::StartCountdown(float TotalTime)
{
	RemainingTime = TotalTime;
	bCountingDown = true;
	SetActorTickEnabled(true);

	if (DisplayUIClass)
	{
		DisplayUI = CreateWidget(GetWorld(), DisplayUIClass);
		DisplayUI->AddToViewport();
	}
}