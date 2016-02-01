// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "RocketProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ship.h"


ARocketProjectile::ARocketProjectile(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer){
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;

	if (Instigator)
	{
		AShip* ownerShip = Cast<AShip>(Instigator->GetPawn());
		int32 theOwnerID = ownerShip->PlayerNumber;
		if (OwnerID != theOwnerID) OwnerID = theOwnerID;
	}
}	

void ARocketProjectile::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);

	AShip* ownerShip = Cast<AShip>(Instigator->GetPawn());
	int32 theOwnerID = ownerShip->PlayerNumber;
	if (OwnerID != theOwnerID) OwnerID = theOwnerID;

	FVector curForward = GetVelocity();
	FVector newForward = FVector::ZeroVector;
	float turnMag = DeltaSeconds * GetVelocity().Size() * handling;
	newForward = curForward + targetDirection * turnMag;
	newForward.ClampMaxSize(curForward.Size());
	ProjectileMovement->Velocity = newForward * 1.1f;
}


