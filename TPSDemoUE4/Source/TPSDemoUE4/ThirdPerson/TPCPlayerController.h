// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSDEMOUE4_API ATPCPlayerController : public APlayerController
{
	GENERATED_BODY()

	bool bAiming;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> CrosshairsClass;

	UUserWidget* Crosshairs;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pitch, meta = (AllowPrivateAccess = "true"))
	float NormalViewPitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pitch, meta = (AllowPrivateAccess = "true"))
	float NormalViewPitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pitch, meta = (AllowPrivateAccess = "true"))
	float AimingViewPitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pitch, meta = (AllowPrivateAccess = "true"))
	float AimingViewPitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Look, meta = (AllowPrivateAccess = "true"))
	float LookHorizontalRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Look, meta = (AllowPrivateAccess = "true"))
	float LookVerticalRate;

public:
	ATPCPlayerController();
	
protected:
	void BeginPlay() override;
	
public:
	void Look(const struct FInputActionValue& Value);
	void SetAiming(bool bAim);

private:
	void SetCrosshairs(bool bShow);
	void SetViewPitchMinMax(bool bAim);
};