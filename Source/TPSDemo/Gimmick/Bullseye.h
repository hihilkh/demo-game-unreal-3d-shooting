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
public:	
	// Sets default values for this actor's properties
	ABullseye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool GetDied() const;
	
private:
	void Die();
};
