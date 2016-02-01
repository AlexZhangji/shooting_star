// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ITP380_RocketThing.h"
#include "ITP380_RocketThingPawn.h"
#include "RocketProjectile.h"
#include "TimerManager.h"
#include "HUDObjects.h"

const FName AITP380_RocketThingPawn::MoveForwardBinding("MoveForward");
const FName AITP380_RocketThingPawn::MoveRightBinding("MoveRight");
const FName AITP380_RocketThingPawn::FireForwardBinding("FireForward");
const FName AITP380_RocketThingPawn::FireRightBinding("FireRight");

AITP380_RocketThingPawn::AITP380_RocketThingPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	//// Create a camera boom...
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->AttachTo(RootComponent);
	//CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	//CameraBoom->TargetArmLength = 2500.f;// change from 1200
	//CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);//(-80.f, 0.f, 0.f);
	//CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	//
	////Fix camera movement
	//CameraBoom->bEnableCameraLag = true;
	//CameraBoom->CameraLagSpeed = 0.1;

	//// Create a camera...
	//CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	//CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	//CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	//CameraComponent->bAbsoluteScale = false;


	// Movement
	MoveDirection = FVector(0., 0., 0.);
	MoveSpeed = 5000.f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 1;
	bCanFire = true;
	
	NumFiredAtOnce = 4;
	NumFiredTotal = 20;
	pauseBetweenFires = .01;

	// Fuel
	fuel = 1000;
}

void AITP380_RocketThingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	/*
	check(InputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAxis(FireForwardBinding);
	InputComponent->BindAxis(FireRightBinding);*/
}

void AITP380_RocketThingPawn::Tick(float DeltaSeconds)
{
	/*

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	//const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	const FVector StickDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f)
		* MoveSpeed / 5;

	// StickDirection acts as an acceleration vector here
	MoveDirection += StickDirection;
	MoveDirection = MoveDirection.ClampMaxSize(2000.0f);	// limit speed so it doesn't go crazy

	// Calculate  movement
	const FVector Movement = MoveDirection * DeltaSeconds;


	// Calculate rotation
	FRotator rRotation = MoveDirection.Rotation();
	FRotator curRotation = GetActorRotation();
	FQuat newRotationQuat = FQuat::Slerp(FQuat(rRotation), FQuat(curRotation), DeltaSeconds*10);
	//this->SetActorRotation(newRotationQuat.Rotator());

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, newRotationQuat.Rotator(), true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, newRotationQuat.Rotator(), true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
	//this->SetActorRotation(FireDirection.Rotation());

	// Try and fire a shot
	FireShot(FireDirection);*/
}

void AITP380_RocketThingPawn::FireShot(FVector FireDirection)
{
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			curFireDirection = FireDirection;
			UWorld* const World = GetWorld();
			/*for (int k = 0; k < NumFiredAtOnce; k++){
				FRotator FireRotation = FireDirection.Rotation();
				FRotator randRotation = FRotator(FireRotation.Pitch, FireRotation.Yaw + FMath::RandRange(-90, 90), FireRotation.Roll);
				// Spawn projectile at an offset from this pawn
				const FVector SpawnLocation = GetActorLocation() + randRotation.RotateVector(GunOffset);

				if (World != NULL)
				{
					// spawn the projectile
					AWeaponProjectile* projectile = World->SpawnActor<AWeaponProjectile>(SpawnLocation, randRotation);
					projectile->targetDirection = FireRotation.Vector();
				}

				//bCanFire = false;

				// try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}
			}*/
			FireCluster();
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AITP380_RocketThingPawn::ShotTimerExpired, FireRate);
			bCanFire = false;

		}
	}
}

void AITP380_RocketThingPawn::FireCluster(){
	UWorld* const World = GetWorld();
	for (int k = 0; k < NumFiredAtOnce; k++){
		FRotator FireRotation = curFireDirection.Rotation();
		FRotator randRotation = FRotator(FireRotation.Pitch, FireRotation.Yaw + FMath::RandRange(-90, 90), FireRotation.Roll);
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + randRotation.RotateVector(GunOffset);

		if (World != NULL)
		{
			// spawn the projectile
			ARocketProjectile* projectile = World->SpawnActor<ARocketProjectile>(SpawnLocation, randRotation);
			projectile->targetDirection = FireRotation.Vector();
		}

		//bCanFire = false;

		// try and play the sound if specified
		
	}
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AITP380_RocketThingPawn::ShotTimerExpired, FireRate);
	projectilesFired += NumFiredAtOnce;
	
	if (projectilesFired < NumFiredTotal)
		World->GetTimerManager().SetTimer(TimerHandle_ShotIntervalExpired, this, &AITP380_RocketThingPawn::FireCluster, pauseBetweenFires);
	else
		projectilesFired = 0;
}

void AITP380_RocketThingPawn::ShotTimerExpired()
{
	bCanFire = true;
}

