// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullseye.h"

#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TPSDemo/Common/HPComponent.h"

// Sets default values
ABullseye::ABullseye()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
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

float ABullseye::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetTriggered())
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

	//UE_LOG(LogTemp, Warning, TEXT("Hit damage : %f, Remaining : %f"), RealDamage, HPComponent->GetCurrentHP());
	if (bDie)
	{
		Trigger(!bCanReuse);
	}
		
	return RealDamage;
}

bool ABullseye::GetTriggered() const
{
	return HPComponent->GetDied();
}

void ABullseye::Trigger(bool bDestroy)
{
	TriggeredDelegate.Broadcast(this);

	if (DieFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DieFX, GetActorLocation());

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController && CameraShakeClass)
		{
			const FVector PlayerPos = PlayerController->GetPawn()->GetActorLocation();
			const float Distance = FVector::Distance(PlayerPos, GetActorLocation());
			float Alpha = (Distance - MinCameraShakeDistance) / (MaxCameraShakeDistance - MinCameraShakeDistance);
			Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
			const float Scale = FMath::Lerp(1.0f, 0.0f, Alpha);
			PlayerController->ClientStartCameraShake(CameraShakeClass, Scale);
		}
	}

	if (bDestroy)
	{
		Destroy();
	}
	else
	{
		SetActive(false);
	}
}

void ABullseye::ReInit()
{
	HPComponent->Reset();
	SetActive(true);
}

void ABullseye::SetActive(bool bActive)
{
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
}
