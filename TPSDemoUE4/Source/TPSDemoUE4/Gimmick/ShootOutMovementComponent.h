// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShootOutMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSDEMOUE4_API UShootOutMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	
	enum class EState : uint8
	{
		Initialized,
		ShootOut,
		DropDown,
	};

	UPROPERTY(EditAnywhere)
	FVector ShootOutVelocity;
	
	UPROPERTY(EditAnywhere)
	float ShootOutTotalDecelerateTime;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEasingFunc::Type> ShootOutDecelerateEasingType;
	
	UPROPERTY(EditAnywhere)
	float Gravity;
	
	UPROPERTY(EditAnywhere)
	float MaxDropDownSpeed;
	
	UPROPERTY(EditAnywhere)
	bool bShootOutWhenBeginPlay = true;
	
	FVector CurrentVelocity;
	EState CurrentState = EState::Initialized;

	float ShootOutDeceleratingTime;
	
public:	
	// Sets default values for this component's properties
	UShootOutMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ShootOut();

	FORCEINLINE void SetShootOutVelocity(const FVector& Velocity) { this->ShootOutVelocity = Velocity; }

private:
	void Update_ShootOut(float DeltaTime);
	void Update_DropDown(float DeltaTime);
	void UpdateVelocity(float DeltaTime);
};
