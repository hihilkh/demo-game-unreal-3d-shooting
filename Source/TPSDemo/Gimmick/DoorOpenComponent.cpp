// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpenComponent.h"

UDoorOpenComponent::UDoorOpenComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpenComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
	InitialPos = GetOwner()->GetActorLocation();
}

void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AnimatingTime += DeltaTime;
	if (AnimatingTime >= MoveTime)
	{
		AnimatingTime = MoveTime;
		SetComponentTickEnabled(false);
	}
	float Alpha = AnimatingTime / MoveTime;

	FVector newPos = FMath::Lerp(InitialPos, InitialPos + MoveDistance, Alpha);
	GetOwner()->SetActorLocation(newPos);
}

void UDoorOpenComponent::Trigger()
{
	AnimatingTime = 0.0f;
	SetComponentTickEnabled(true);
}