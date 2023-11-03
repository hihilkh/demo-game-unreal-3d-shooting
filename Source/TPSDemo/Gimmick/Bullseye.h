// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullseye.generated.h"

UCLASS()
class TPSDEMO_API ABullseye : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggeredDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerFailedDelegate);
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HP, meta = (AllowPrivateAccess = "true"))
	class UHPComponent* HPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damage, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageType> AcceptDamageType;

	UPROPERTY(EditAnywhere, Category = Explosion)
	class UNiagaraSystem* DieFX;

	UPROPERTY(EditAnywhere, Category = Explosion)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, Category = Explosion)
	float MinCameraShakeDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = Explosion)
	float MaxCameraShakeDistance = 1200.0f;
	
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FTriggeredDelegate TriggeredDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FTriggerFailedDelegate TriggerFailedDelegate;
	
public:	
	// Sets default values for this actor's properties
	ABullseye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool GetDied() const;
	
	void DestroyWithTrigger(bool bTriggerFailed);

private:
	void Die();
};
