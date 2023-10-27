// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCPlayerController.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"

void ATPCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bAiming = false;
	Crosshairs = CreateWidget(this, CrosshairsClass);
	SetCrosshairs(bAiming);
}


void ATPCPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
	if (bAiming)
	{
		if (APawn* Pawn = GetPawn())
		{
			Pawn->AddActorLocalRotation(FRotator(0.0, LookAxisVector.X * GetDeprecatedInputYawScale(), 0.0));
		}
	}
}

void ATPCPlayerController::SetAiming(bool bAim)
{
	if (bAiming == bAim)
	{
		return;
	}

	bAiming = bAim;
	SetCrosshairs(bAiming);
}

void ATPCPlayerController::SetCrosshairs(bool bShow)
{
	if (Crosshairs != nullptr)
	{
		if (bShow)
		{
			Crosshairs->AddToViewport();
		}
		else
		{
			Crosshairs->RemoveFromParent();
		}
	}
}
