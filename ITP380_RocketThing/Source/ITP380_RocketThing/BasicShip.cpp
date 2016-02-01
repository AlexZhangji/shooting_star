// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "BasicShip.h"


ABasicShip::ABasicShip(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    //Setting BasicShip's values (CHANGE THEM; THESE ARE ARBITRARY VALUES)
    health = 100.f; // changed health from 10 to 100
	MaxHealth = 100.f; // added for blueprints health bar
	armor = 0.1;
	
	//init ship stats
	MaxMana = 100;
	Mana = MaxMana;

    //weapon = new SomeWeapon;
    
}

// Called when the game starts or when spawned
void ABasicShip::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ABasicShip::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
	if (bIsChargingMovement&&MovementCharge<MovementChargeTime){
		MovementCharge += DeltaTime;
		MovementCharge = FMath::Min(MovementCharge, MovementChargeTime);
	}
}

// Called to bind functionality to input
void ABasicShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    //Super::SetupPlayerInputComponent(InputComponent);
    
}

void ABasicShip::StartSpecialMovement(){
	bIsChargingMovement = true;
}

void ABasicShip::EndSpecialMovement(){
	FVector Forward = GetActorForwardVector();
	float MovementSpeed = ShipMeshComponent->GetPhysicsLinearVelocity().Size() * MovementCharge / MovementChargeTime * 1.5;
	MovementSpeed = FMath::Clamp<float>(MovementSpeed, 0, MaxSpeed);
	Forward *= MovementSpeed;
	ShipMeshComponent->SetPhysicsLinearVelocity(Forward);
	bIsChargingMovement = false;
	MovementCharge = 0;
}

