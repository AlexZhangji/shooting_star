// Copyright 1998-2015 Epic Games, Inc. All Rights Reserve

#include "ITP380_RocketThing.h"
#include "WeaponProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ship.h"

AWeaponProjectile::AWeaponProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = FirableMesh;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	
	if (Instigator)
	{
		AShip* ownerShip = Cast<AShip>(Instigator->GetPawn());
		int32 theOwnerID = ownerShip->PlayerNumber;
		if (OwnerID != theOwnerID) OwnerID = theOwnerID;
	}

	StartSpeed = 3000;
}

void AWeaponProjectile::BeginPlay(){
	Super::BeginPlay();
	ProjectileMovement->InitialSpeed = StartSpeed;
}



