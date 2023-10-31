// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TPSDEMO_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool TryShoot();
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ShootStartRefPoint;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* ShootLightFXComponent;

	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	float ReloadTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	float Damage = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	TSubclassOf<class UGunDamageType> DamageType;
	
	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	float ShootRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = Shoot)
	class UNiagaraSystem* SparkFX;
    	
	float RemainingReloadTime = 0.0f;

protected:
	virtual bool CanShoot() const;
	virtual void Shoot();
	virtual FVector CalculateShootStartPos(const FVector& ViewPointStart, const FRotator& ViewPointRotation) const;
};
