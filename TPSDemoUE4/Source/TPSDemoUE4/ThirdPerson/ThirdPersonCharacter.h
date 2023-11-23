// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharacter.generated.h"

class AGun;

// ThirdPersonCharacterの略：TPC
UCLASS(config=Game)
class AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* AimingCameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* AimingCameraChild;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aiming, meta = (AllowPrivateAccess = "true"))
	float AimingMaxWalkSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float NormalMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aiming, meta = (AllowPrivateAccess = "true"))
	float AimingCameraBlendTime;
	
	UPROPERTY(BlueprintReadOnly, Category = Aiming, meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
	
public:
	AThirdPersonCharacter();
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void Jump() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Rate);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void Aim();
	void StopAiming();
	void Attack();
	

	UFUNCTION(BlueprintCallable)
	void SetInputMode(bool bUIMode, bool bForceAssign = true);
	
private:
	void SetAiming(bool bAim);
	
	UFUNCTION(BlueprintCallable, Category = Camera, meta = (AllowPrivateAccess = "true"))
	void ResetCameraTransform(bool bAim);
};

