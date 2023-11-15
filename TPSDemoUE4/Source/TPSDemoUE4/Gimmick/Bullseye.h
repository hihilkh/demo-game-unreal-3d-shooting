// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullseye.generated.h"

UCLASS()
class TPSDEMOUE4_API ABullseye : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggeredDelegate, ABullseye*, Sender);
	
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
	
	UPROPERTY(BlueprintAssignable, Category = Event)
	FTriggeredDelegate TriggeredDelegate;

	/** TriggeredDelegateを2回以上Broadcastできるか */
	UPROPERTY(EditAnywhere, Category = Event)
	bool bCanReuse = false;
	
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

	FORCEINLINE FTriggeredDelegate& OnTriggered() { return TriggeredDelegate; }
	
	UFUNCTION(BlueprintPure)
	bool GetTriggered() const;

	UFUNCTION(BlueprintCallable)
	void ReInit();

	FORCEINLINE void SetReuse(bool bReuse) { bCanReuse = bReuse; }

	void SetActive(bool bActive);
	
private:
	void Trigger(bool bDestroy);
};
