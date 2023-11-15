// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPCPlayerController.h"
#include "TPSDemoUE4/Weapon/Gun.h"


//////////////////////////////////////////////////////////////////////////
// AThirdPersonCharacter

AThirdPersonCharacter::AThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AimingCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("AimingCameraBoom"));
	AimingCameraBoom->SetupAttachment(RootComponent);
	AimingCameraBoom->TargetArmLength = 100.0f;
	AimingCameraBoom->bUsePawnControlRotation = true;
	
	AimingCameraChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("AimingCameraChild"));
	AimingCameraChild->SetupAttachment(AimingCameraBoom);
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AimingMaxWalkSpeed = 300.0f;
	AimingCameraBlendTime = 0.2f;
	bAiming = false;
}

void AThirdPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	SetInputMode(false, false);
	
	NormalMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r_gun"));
		Gun->SetOwner(this);
		//Gun->SetActorHiddenInGame(true);
	}
	
	ResetCameraTransform(bAiming);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AThirdPersonCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonCharacter::LookUpAtRate);
	
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AThirdPersonCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AThirdPersonCharacter::StopAiming);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AThirdPersonCharacter::Attack);
}

void AThirdPersonCharacter::SetInputMode(bool bUIMode, bool bForceAssign)
{
	if (ATPCPlayerController* PlayerController = Cast<ATPCPlayerController>(Controller))
	{
		// TODO
	}
}

void AThirdPersonCharacter::Jump()
{
	if (bAiming)
	{
		return;
	}
	
	Super::Jump();
}

void AThirdPersonCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		if (bAiming)
		{
			AddMovementInput(GetActorForwardVector(), Value);
		}
		else
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// add movement 
			AddMovementInput(ForwardDirection, Value);
		}
	}
}

void AThirdPersonCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		if (bAiming)
		{
			AddMovementInput(GetActorRightVector(), Value);
		}
		else
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			AddMovementInput(RightDirection, Value);
		}
	}
}

void AThirdPersonCharacter::Turn(float Val)
{
	if (ATPCPlayerController* PlayerController = Cast<ATPCPlayerController>(Controller))
	{
		PlayerController->Turn(Val);
	}
}

void AThirdPersonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	Turn(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonCharacter::Aim()
{
	if (GetMovementComponent()->IsFalling())
	{
		SetAiming(false);
	}
	else
	{
		SetAiming(true);
	}
}

void AThirdPersonCharacter::StopAiming()
{
	SetAiming(false);
}

void AThirdPersonCharacter::SetAiming(bool bAim)
{
	if (bAiming == bAim)
	{
		return;
	}
	
	bAiming = bAim;
	GetCharacterMovement()->MaxWalkSpeed = bAim ? AimingMaxWalkSpeed : NormalMaxWalkSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = !bAim;
	//Gun->SetActorHiddenInGame(!bAim);

	if (ATPCPlayerController* PlayerController = Cast<ATPCPlayerController>(Controller))
	{
		ResetCameraTransform(bAim);
		
		PlayerController->SetViewTargetWithBlend(
			bAim ? AimingCameraChild->GetChildActor() : this,
			AimingCameraBlendTime,
			VTBlend_Linear,
			0,
			true);

		PlayerController->SetAiming(bAim);
	}
}

void AThirdPersonCharacter::ResetCameraTransform(bool bAim)
{
	if (Controller != nullptr)
	{
		if (bAim)
		{
			FVector Start;
			FRotator Rotation;
			Controller->GetPlayerViewPoint(Start, Rotation);
			SetActorRotation(FRotator(0, Rotation.Yaw, 0));
		}
		
		USpringArmComponent* SpringArm = bAim ? AimingCameraBoom : CameraBoom;
		Controller->SetControlRotation(SpringArm->GetComponentRotation());
	}
}

void AThirdPersonCharacter::Attack()
{
	if (bAiming)
	{
		if (Gun)
		{
			Gun->TryShoot();
		}
	}
	else
	{
		// TODO
	}
}
