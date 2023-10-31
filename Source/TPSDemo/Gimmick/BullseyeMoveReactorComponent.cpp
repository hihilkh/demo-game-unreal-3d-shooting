// Fill out your copyright notice in the Description page of Project Settings.


#include "BullseyeMoveReactorComponent.h"

UBullseyeMoveReactorComponent::UBullseyeMoveReactorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBullseyeMoveReactorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
	InitialPos = GetOwner()->GetActorLocation();
}

void UBullseyeMoveReactorComponent::Trigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger"));
	AnimatingTime = 0.0f;
	SetComponentTickEnabled(true);
}

void UBullseyeMoveReactorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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