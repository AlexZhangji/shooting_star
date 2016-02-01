// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "ShieldPickup.h"

// Sets default values
AShieldPickup::AShieldPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Pickup Mesh"));
	RootComponent = PickupMesh;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->AttachTo(RootComponent);
}

void AShieldPickup::AffectShip(AShip* ShipPlayer){
	ShipPlayer->ActivateShiledWithoutMana();
}