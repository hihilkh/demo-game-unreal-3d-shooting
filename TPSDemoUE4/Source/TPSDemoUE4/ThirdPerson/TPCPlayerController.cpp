// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCPlayerController.h"
#include "Blueprint/UserWidget.h"

ATPCPlayerController::ATPCPlayerController() :
	bAiming(false),
	NormalViewPitchMin(-89.0f),
	NormalViewPitchMax(89.0f),
	AimingViewPitchMin(-45.0f),
	AimingViewPitchMax(30.0f)
{
}

void ATPCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Crosshairs = CreateWidget(this, CrosshairsClass);
	Crosshairs->AddToViewport();
	SetAiming(bAiming);
}

void ATPCPlayerController::Turn(float Val)
{
	AddYawInput(Val);
	if (bAiming)
	{
		if (APawn* MyPawn = GetPawn())
		{
			MyPawn->AddActorLocalRotation(FRotator(0.0, Val * InputYawScale, 0.0));
		}
	}
}

void ATPCPlayerController::SetAiming(bool bAim)
{
	bAiming = bAim;
	SetCrosshairs(bAim);
	SetViewPitchMinMax(bAim);
}

void ATPCPlayerController::SetCrosshairs(bool bShow)
{
	if (Crosshairs != nullptr)
	{
		if (bShow)
		{
			Crosshairs->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Crosshairs->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATPCPlayerController::SetViewPitchMinMax(bool bAim)
{
	PlayerCameraManager->ViewPitchMin = bAim ? AimingViewPitchMin : NormalViewPitchMin;
	PlayerCameraManager->ViewPitchMax = bAim ? AimingViewPitchMax : NormalViewPitchMax;
}
	
