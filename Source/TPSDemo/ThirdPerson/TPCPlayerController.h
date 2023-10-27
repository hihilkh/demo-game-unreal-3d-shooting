// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSDEMO_API ATPCPlayerController : public APlayerController
{
	GENERATED_BODY()

	bool bAiming;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> CrosshairsClass;

	UUserWidget* Crosshairs;
	
protected:
	void BeginPlay() override;
	
public:
	void Look(const struct FInputActionValue& Value);
	void SetAiming(bool bAim);

private:
	void SetCrosshairs(bool bShow);
};
