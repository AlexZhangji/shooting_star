// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "ManaPickup.h"


AManaPickup::AManaPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mana Pickup Mesh"));
	RootComponent = PickupMesh;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->AttachTo(RootComponent);
}

void AManaPickup::AffectShip(AShip* ShipPlayer)
{
	int MaxMana = 100;
	int ManaAmount = 30;
	if (ShipPlayer->Mana <= MaxMana && ShipPlayer->Mana >= (MaxMana - ManaAmount)){
		ShipPlayer->Mana = MaxMana;
	}
	else if (ShipPlayer->Mana <= (MaxMana - ManaAmount)){
		ShipPlayer->Mana += ManaAmount;
	}
}

