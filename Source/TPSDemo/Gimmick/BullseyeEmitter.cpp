// Fill out your copyright notice in the Description page of Project Settings.


#include "BullseyeEmitter.h"

#include "Bullseye.h"
#include "ShootOutMovementComponent.h"

// Sets default values
ABullseyeEmitter::ABullseyeEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullseyeEmitter::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickEnabled(false);
}

// Called every frame
void ABullseyeEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	EmittingAcumulatedTime += DeltaTime;

	if (TriggerFailedTime < 0.0f)
	{
		return;
	}
	
	if (EmittingAcumulatedTime > TriggerFailedTime)
	{
		TriggerFail();
	}
}

void ABullseyeEmitter::Emit()
{
	if (bEmitting)
	{
		UE_LOG(LogTemp, Warning, TEXT("すでに発射した。もう一度発射できない。"));
		return;
	}

	bEmitting = true;
	EmittingAcumulatedTime = 0.0f;

	for(const auto& Velocity : EmitVelocityArray)
	{
		ABullseye* Bullseye = GetWorld()->SpawnActor<ABullseye>(BullseyeClass);
		Bullseye->SetOwner(this);
		Bullseye->SetActorLocation(GetActorLocation());
		Bullseye->OnTriggered().AddDynamic(this, &ABullseyeEmitter::BullseyeTriggeredHandler);
		EmittedBullseyeArray.Add(Bullseye);
		
		if (auto ShootOutMovementComponent = Bullseye->GetComponentByClass<UShootOutMovementComponent>())
		{
			ShootOutMovementComponent->SetShootOutVelocity(Velocity);
			ShootOutMovementComponent->ShootOut();
		}
	}

	SetActorTickEnabled(true);
}

void ABullseyeEmitter::Trigger(bool bDestroy)
{
	TriggeredDelegate.Broadcast(this);

	if (bDestroy)
	{
		Destroy();
	}
	else
	{
		SetActorTickEnabled(false);
		bEmitting = false;
	}
}

void ABullseyeEmitter::TriggerFail()
{
	if (!bEmitting)
	{
		return;
	}
	
	TriggerFailedDelegate.Broadcast(this);
	SetActorTickEnabled(false);
	bEmitting = false;

	for (auto Bullseye : EmittedBullseyeArray)
	{
		Bullseye->Destroy();
	}

	EmittedBullseyeArray.Empty();
}

void ABullseyeEmitter::ReInit()
{
	TriggerFail();
}

void ABullseyeEmitter::BullseyeTriggeredHandler(ABullseye* Sender)
{
	EmittedBullseyeArray.RemoveSingle(Sender);

	if (EmittedBullseyeArray.Num() == 0)
	{
		Trigger(!bCanReuse);
	}
}