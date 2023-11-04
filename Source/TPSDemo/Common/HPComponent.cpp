// Fill out your copyright notice in the Description page of Project Settings.


#include "HPComponent.h"

// Sets default values for this component's properties
UHPComponent::UHPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHPComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHP = TotalHP;
}


// Called every frame
void UHPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHPComponent::TakeDamage(float& Damage, bool& bDied)
{
	Damage = FMath::Min(CurrentHP, Damage);
	CurrentHP -= Damage;
	bDied = GetDied();
}

void UHPComponent::Reset()
{
	CurrentHP = TotalHP;
}