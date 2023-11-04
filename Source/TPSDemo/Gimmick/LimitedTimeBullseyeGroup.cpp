// Fill out your copyright notice in the Description page of Project Settings.


#include "LimitedTimeBullseyeGroup.h"

#include "Bullseye.h"
#include "TPSDemo/Common/CountdownTimer.h"

// Sets default values
ALimitedTimeBullseyeGroup::ALimitedTimeBullseyeGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALimitedTimeBullseyeGroup::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Children;
	GetAllChildActors(Children, true);
	for (auto Child : Children)
	{
		if (ABullseye* Bullseye = Cast<ABullseye>(Child))
		{
			BullseyeArray.Add(Bullseye);
			Bullseye->SetReuse(true);
			Bullseye->OnTriggered().AddDynamic(this, &ALimitedTimeBullseyeGroup::BullseyeTriggeredHandler);
		}
	}

	SetAllBullseyeActive(false);
	SetActorTickEnabled(false);
}

void ALimitedTimeBullseyeGroup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Timer)
	{
		Timer->Destroy();
		Timer = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ALimitedTimeBullseyeGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentResetWaitingTime += DeltaTime;

	if (CurrentResetWaitingTime > ResetWaitTime)
	{
		TriggerFail();
		SetActorTickEnabled(false);
		
		if (Timer)
		{
			Timer->Destroy();
			Timer = nullptr;
		}
	}

}

void ALimitedTimeBullseyeGroup::SetAllBullseyeActive(bool bActive)
{
	for (auto Bullseye : BullseyeArray)
	{
		Bullseye->SetActive(bActive);
	}
}

void ALimitedTimeBullseyeGroup::StartCountdown()
{
	CurrentTriggeredBullseyeCount = 0;
	for (auto Bullseye : BullseyeArray)
	{
		Bullseye->ReInit();
	}
	SetAllBullseyeActive(true);
	
	if (!Timer && TimerClass)
	{
		Timer = GetWorld()->SpawnActor<ACountdownTimer>(TimerClass);
		Timer->SetOwner(this);
		Timer->OnTimeUp().AddDynamic(this, &ALimitedTimeBullseyeGroup::TimerUpHandler);
	}

	Timer->StartCountdown(TimeLimit);
}

void ALimitedTimeBullseyeGroup::Trigger()
{
	TriggeredDelegate.Broadcast(this);
	Destroy();
}

void ALimitedTimeBullseyeGroup::TriggerFail()
{
	TriggerFailedDelegate.Broadcast(this);
}

void ALimitedTimeBullseyeGroup::TimerUpHandler(ACountdownTimer* Sender)
{
	CurrentResetWaitingTime = 0.0f;
	SetAllBullseyeActive(false);
	SetActorTickEnabled(true);
}

void ALimitedTimeBullseyeGroup::BullseyeTriggeredHandler(ABullseye* Sender)
{
	++CurrentTriggeredBullseyeCount;
	
	if (CurrentTriggeredBullseyeCount == BullseyeArray.Num())
	{
		Trigger();
	}
}
