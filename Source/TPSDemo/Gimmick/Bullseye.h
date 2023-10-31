// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullseye.generated.h"

UCLASS()
class TPSDEMO_API ABullseye : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HP, meta = (AllowPrivateAccess = "true"))
	class UHPComponent* HPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damage, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageType> AcceptDamageType;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	class UNiagaraSystem* DieFX;
	
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

	DECLARE_EVENT(ABullseye, FTriggeredEvent);
	FTriggeredEvent& OnTriggered() { return TriggeredEvent; }

private:
	FTriggeredEvent TriggeredEvent;
	
private:
	void Die();
};
