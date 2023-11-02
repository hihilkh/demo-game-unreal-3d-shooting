// Fill out your copyright notice in the Description page of Project Settings.


#include "BullseyeEventListener.h"

#include "Bullseye.h"
#include "BullseyeEventHandler.h"

// Sets default values for this component's properties
UBullseyeEventListener::UBullseyeEventListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	EventReceiver = GetOwner();
}


// Called when the game starts
void UBullseyeEventListener::BeginPlay()
{
	Super::BeginPlay();

	if (EventReceiver)
	{
		EventHandler = EventReceiver->GetComponentByClass<UBullseyeEventHandler>();
	}
	
	if (!EventName.IsEmpty() && EventHandler)
	{
		ABullseye::OnTriggered().AddUObject(this, &UBullseyeEventListener::Trigger);
		ABullseye::OnTriggerFailed().AddUObject(this, &UBullseyeEventListener::TriggerFail);
	}
}


// Called every frame
void UBullseyeEventListener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBullseyeEventListener::Trigger(const FString& Name)
{
	if (this->EventName != Name)
	{
		return;
	}
	
	if (!EventHandler)
	{
		return;
	}

	++TriggerCount;

	if (TriggerCount == CountToTrigger)
	{
		EventHandler->Trigger();
	}
}

void UBullseyeEventListener::TriggerFail(const FString& Name)
{
	if (this->EventName != Name)
	{
		return;
	}

	if (!EventHandler)
	{
		return;
	}

	TriggerCount = 0;
	EventHandler->TriggerFail();
}