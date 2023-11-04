// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootOutMovementComponent.h"

// Sets default values for this component's properties
UShootOutMovementComponent::UShootOutMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootOutMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bShootOutWhenBeginPlay)
	{
		ShootOut();
	}
	else
	{
		SetComponentTickEnabled(false);
	}

}


// Called every frame
void UShootOutMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch(CurrentState)
	{
		case EState::ShootOut:	Update_ShootOut(DeltaTime);	break;
		case EState::DropDown:	Update_DropDown(DeltaTime);	break;
	}
}

void UShootOutMovementComponent::ShootOut()
{
	if (CurrentState != EState::Initialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("すでにShootOutした。もう一度ShootOutできない。"));
		return;
	}
	
	CurrentVelocity = ShootOutVelocity;
	CurrentState = EState::ShootOut;
	ShootOutDeceleratingTime = 0.0f;
	SetComponentTickEnabled(true);
}

void UShootOutMovementComponent::Update_ShootOut(float DeltaTime)
{
	ShootOutDeceleratingTime += DeltaTime;
	float Alpha = ShootOutTotalDecelerateTime == 0.0f ? 1.0f : ShootOutDeceleratingTime / ShootOutTotalDecelerateTime;

	if (Alpha >= 1.0f)
	{
		Alpha = 1.0f;
		CurrentState= EState::DropDown;
	}
	
	float EasedAlpha = UKismetMathLibrary::Ease(0.0, 1.0, Alpha, ShootOutDecelerateEasingType);
	CurrentVelocity = FMath::Lerp(ShootOutVelocity, FVector::Zero(), EasedAlpha);
	
	UpdateVelocity(DeltaTime);
}

void UShootOutMovementComponent::Update_DropDown(float DeltaTime)
{
	CurrentVelocity.Z -= Gravity * DeltaTime;
	CurrentVelocity.Z = FMath::Max(CurrentVelocity.Z, -MaxDropDownSpeed);

	UpdateVelocity(DeltaTime);
}

void UShootOutMovementComponent::UpdateVelocity(float DeltaTime)
{
	FVector Location = GetOwner()->GetActorLocation();
	Location += CurrentVelocity * DeltaTime;
	GetOwner()->SetActorLocation(Location);
}