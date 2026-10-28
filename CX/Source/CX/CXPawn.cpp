// Copyright Epic Games, Inc. All Rights Reserved.

#include "CXPawn.h"
#include "CXWheelFront.h"
#include "CXWheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/CXPlayerState.h"
#include "Engine/DamageEvents.h"
#include "GameState/CXGameState.h"
#include "Gimmic/CXLandMine.h"
#include "Net/UnrealNetwork.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

DEFINE_LOG_CATEGORY(LogTemplateVehicle);

ACXPawn::ACXPawn()
{
	// construct the front camera boom
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = false;

	// construct the back camera boom
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bEnableCameraRotationLag = true;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Configure the car mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	// get the Chaos Wheeled movement component
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

}

void ACXPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ACXPawn::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ACXPawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ACXPawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ACXPawn::Throttle);

		// break 
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ACXPawn::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &ACXPawn::StartBrake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ACXPawn::StopBrake);

		// handbrake 
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &ACXPawn::StartHandbrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ACXPawn::StopHandbrake);

		// look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ACXPawn::LookAround);

		// toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &ACXPawn::ToggleCamera);

		// reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &ACXPawn::ResetVehicle);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACXPawn::InputAction);
		EnhancedInputComponent->BindAction(LandMineAction, ETriggerEvent::Started, this, &ACXPawn::HandleLandMineInput);
	}
	else
	{
		UE_LOG(LogTemplateVehicle, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

bool ACXPawn::CanControlVehicle() const
{
	const ACXGameState* GS = GetWorld()->GetGameState<ACXGameState>();
	return IsValid(GS) && GS->GetCurrentGameState() == EGameState::Playing;
}

void ACXPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	UChaosWheeledVehicleMovementComponent* Movement = GetChaosVehicleMovement();
	if (IsValid(Movement) == false)
	{
		return;
	}

	if (IsLocallyControlled() == true)
	{
		if (bThrottleBroken)
		{
			Movement->SetThrottleInput(0.f);
		}

		if (CanControlVehicle() == false)
		{
			Movement->SetThrottleInput(0.f);
			Movement->SetSteeringInput(0.f);
			Movement->SetHandbrakeInput(true);
			bGameStateHandbrakeLocked = true;
		}
		else if (bGameStateHandbrakeLocked)
		{
			Movement->SetHandbrakeInput(false);
			bGameStateHandbrakeLocked = false;
		}
	}
	// add some angular damping if the vehicle is in midair
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);

	// realign the camera yaw to face front
	float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, Delta, 1.0f);

	BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
}

float ACXPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ACXPawn* Attacker = Cast<ACXPawn>(DamageCauser);
	if (ActualDamage <= 0 || DamageCauser == this || HasAuthority() == false || Attacker == nullptr)
	{
		return 0.f;
	}
	// 맞은 사람
	ACXPlayerState* VictimPlayerState = GetPlayerState<ACXPlayerState>();
	// 때린 사람
	ACXPlayerState* AttackerPlayerState = Attacker->GetPlayerState<ACXPlayerState>();
	if (IsValid(VictimPlayerState) == false || IsValid(AttackerPlayerState) == false)
	{
		return 0.f;
	}

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		const FPointDamageEvent& PointEvent = static_cast<const FPointDamageEvent&>(DamageEvent);
		if (IsWheelBone(PointEvent.HitInfo.BoneName))
		{
			UE_LOG(LogTemplateVehicle, Warning, TEXT("Wheel Hit: %s"), *PointEvent.HitInfo.BoneName.ToString());
			VictimPlayerState->ApplyWheelHitPenalty();
		}
	}

	const int32 TransferCoinAmount = (int32)ActualDamage;
	if (VictimPlayerState->TryRemoveCoins((int32)ActualDamage))
	{
		UE_LOG(LogTemplateVehicle, Warning, TEXT("%s transferred %d coins to %s"), *GetNameSafe(VictimPlayerState), TransferCoinAmount, *GetNameSafe(AttackerPlayerState));
		AttackerPlayerState->AddCoins(TransferCoinAmount);	
	}

	else
	{
		UE_LOG(LogTemplateVehicle, Warning, TEXT("%s has no coins to transfer %s"), *GetNameSafe(VictimPlayerState), *GetNameSafe(AttackerPlayerState));
	}

	return ActualDamage;
}

bool ACXPawn::IsWheelBone(const FName& InBoneName) const
{
	for (const FChaosWheelSetup& Wheel : GetChaosVehicleMovement()->WheelSetups)
	{
		if (Wheel.BoneName == InBoneName)
		{
			return true;
		}
	}
	return false;
}

void ACXPawn::Steering(const FInputActionValue& Value)
{
	if (CanControlVehicle() == false)
	{
		return;
	}
	// get the input magnitude for steering
	float SteeringValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void ACXPawn::Throttle(const FInputActionValue& Value)
{
	if (CanControlVehicle() == false || bThrottleBroken)
	{
		return;
	}
	// get the input magnitude for the throttle
	float ThrottleValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void ACXPawn::Brake(const FInputActionValue& Value)
{
	if (CanControlVehicle() == false)
	{
		return;
	}
	// get the input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void ACXPawn::StartBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ACXPawn::StopBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(false);

	// reset brake input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void ACXPawn::StartHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(true);

	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void ACXPawn::StopHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(false);

	// call the Blueprint hook for the break lights
	BrakeLights(false);
}

void ACXPawn::LookAround(const FInputActionValue& Value)
{
	// get the flat angle value for the input 
	float LookValue = Value.Get<float>();

	// add the input
	BackSpringArm->AddLocalRotation(FRotator(0.0f, LookValue, 0.0f));
}

void ACXPawn::ToggleCamera(const FInputActionValue& Value)
{
	// toggle the active camera flag
	bFrontCameraActive = !bFrontCameraActive;

	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void ACXPawn::ResetVehicle(const FInputActionValue& Value)
{
	if (CanControlVehicle() == false)
	{
		return;
	}
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;
	
	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemplateVehicle, Error, TEXT("Reset Vehicle"));
}

void ACXPawn::InputAction(const FInputActionValue& Value)
{
	if (CanControlVehicle() == false)
	{
		return;
	}

	CTSAttack();
}

void ACXPawn::HandleLandMineInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateVehicle, Warning, TEXT("[LandMine] 1. Input pressed (Local=%d)"), IsLocallyControlled());

	if (IsLocallyControlled() == true)
	{
		ServerRPCSpawnLandMine();
	}
}

void ACXPawn::ServerRPCSpawnLandMine_Implementation()
{
	UE_LOG(LogTemplateVehicle, Warning, TEXT("[LandMine] 2. ServerRPC arrived (CanControl=%d, Class=%s)"),
		CanControlVehicle(), *GetNameSafe(LandMineClass));

	if (CanControlVehicle() == false || IsValid(LandMineClass) == false)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnedLocation = (GetActorLocation() + GetActorForwardVector() * 300.f) - FVector(0.f, 0.f, 90.f);
	ACXLandMine* SpawnedLandMine = GetWorld()->SpawnActor<ACXLandMine>(LandMineClass, SpawnedLocation, FRotator::ZeroRotator, SpawnParams);
		
	UE_LOG(LogTemplateVehicle, Warning, TEXT("[LandMine] 3. Spawned=%s at %s"), *GetNameSafe(SpawnedLandMine), *SpawnedLocation.ToString());
	DrawDebugSphere(GetWorld(), SpawnedLocation, 50.f, 12, FColor::Yellow, false, 5.f);
}

bool ACXPawn::ServerRPCSpawnLandMine_Validate()
{
	return true;
}

void ACXPawn::MulticastHitEffect_Implementation(const FVector& TraceStart, const FVector& TraceEnd, bool bHitVehicle, FVector ImpactPoint, FVector ImpactNormal)
{
	UWorld* World = GetWorld();
	DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 3.0f);

	if (!bHitVehicle)
	{
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(World, HitParticle, ImpactPoint, ImpactNormal.Rotation());
}

void ACXPawn::CTSAttack_Implementation()
{
	if (CanControlVehicle() == false)
	{
		return;
	}

	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * 700.0f;

	UWorld* World = GetWorld();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHitVehicle = false;
	FHitResult HitResult;
	if (World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		AActor* Actor = HitResult.GetActor();
		UE_LOG(LogTemplateVehicle, Warning, TEXT("Attack trace hit: %s"), *GetNameSafe(HitResult.GetActor()));

		if (ACXPawn* CXPawn = Cast<ACXPawn>(Actor))
		{
			bHitVehicle = true;
			UGameplayStatics::ApplyPointDamage(CXPawn, 5.f, GetActorForwardVector(), HitResult, GetController(), this, nullptr);
		}
	}

	MulticastHitEffect(Start, End, bHitVehicle, HitResult.ImpactPoint, HitResult.ImpactNormal);
}

void ACXPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bThrottleBroken);
}

void ACXPawn::ApplyThrottleFailure(float Duration)
{
	if (HasAuthority() == false)
	{
		return;
	}

	bThrottleBroken = true;
	ForceNetUpdate(); // 즉시 반영

	GetWorldTimerManager().SetTimer(ThrottleFailureTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			bThrottleBroken = false;
			ForceNetUpdate();
		}), Duration, false);
}

#undef LOCTEXT_NAMESPACE