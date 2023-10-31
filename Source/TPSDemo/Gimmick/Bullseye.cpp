// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullseye.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"
#include "TPSDemo/Common/HPComponent.h"

// Sets default values
ABullseye::ABullseye()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	HPComponent = CreateDefaultSubobject<UHPComponent>(TEXT("HPComponent"));
}

// Called when the game starts or when spawned
void ABullseye::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullseye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABullseye::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetDied())
	{
		return 0.0f;
	}

	if (!UKismetMathLibrary::ClassIsChildOf(DamageEvent.DamageTypeClass, AcceptDamageType))
	{
		return 0.0f;
	}

	float RealDamage = DamageAmount;
	bool bDie = false;
	HPComponent->TakeDamage(RealDamage, bDie);
	Super::TakeDamage(RealDamage, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Hit damage : %f, Remaining : %f"), RealDamage, HPComponent->GetCurrentHP());
	if (bDie)
	{
		Die();
	}
		
	return RealDamage;
}

bool ABullseye::GetDied() const
{
	return HPComponent->GetDied();
}

void ABullseye::Die()
{
	// TODO
}
