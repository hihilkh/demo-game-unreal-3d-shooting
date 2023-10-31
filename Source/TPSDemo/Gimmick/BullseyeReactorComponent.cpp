// Fill out your copyright notice in the Description page of Project Settings.


#include "BullseyeReactorComponent.h"

#include "Bullseye.h"

// Sets default values for this component's properties
UBullseyeReactorComponent::UBullseyeReactorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBullseyeReactorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (TriggerSource)
	{
		TriggerSource->OnTriggered().AddUObject(this, &UBullseyeReactorComponent::Trigger);
	}
	
}


// Called every frame
void UBullseyeReactorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}