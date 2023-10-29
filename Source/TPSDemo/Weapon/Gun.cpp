// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	ShootStartRefPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShootStartRefPoint"));
	ShootStartRefPoint->SetupAttachment(Root);

	ReloadTime = 0.5f;
	Damage = 1;
	ShootRange = 1000.0f;
	RemainingReloadTime = 0.0f;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RemainingReloadTime > 0.0f)
	{
		RemainingReloadTime -= DeltaTime;
		RemainingReloadTime = FMath::Max(0.0f, RemainingReloadTime);
	}
}

bool AGun::TryShoot()
{
	const bool bCanShoot = CanShoot();

	if (bCanShoot)
	{
		Shoot();
	}

	return bCanShoot;
}

bool AGun::CanShoot() const
{
	return RemainingReloadTime <= 0.0f;
}

void AGun::Shoot()
{
	APawn* Owner = Cast<APawn>(GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	AController* Controller = Owner->GetController();
	if (Controller == nullptr)
	{
		return;
	}

	RemainingReloadTime = ReloadTime;
	
	FVector ViewPointStart;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(ViewPointStart, Rotation);
	
	const FVector Start = CalculateShootStartPos(ViewPointStart, Rotation);
	const FVector End = Start + Rotation.Vector() * ShootRange;
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);

	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1);
	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
	}
}

FVector AGun::CalculateShootStartPos(const FVector& ViewPointStart, const FRotator& ViewPointRotation) const
{
	FVector DeltaVector = ShootStartRefPoint->GetComponentLocation() - ViewPointStart;
	FVector DirectionVector = ViewPointRotation.Vector();
	return ViewPointStart + DirectionVector * DeltaVector.Dot(DirectionVector);
}