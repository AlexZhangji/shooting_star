// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupActor.h"
#include "ShieldPickup.generated.h"

/**
 *  This is a randomly spawned shield pickup that give ships shield ability for a limited amount of time
 */
class ASpawningVolume;

UCLASS()
class ITP380_ROCKETTHING_API AShieldPickup : public APickupActor
{
	GENERATED_BODY()

	AShieldPickup();
	
	virtual void AffectShip(AShip* ShipPlayer);
};
