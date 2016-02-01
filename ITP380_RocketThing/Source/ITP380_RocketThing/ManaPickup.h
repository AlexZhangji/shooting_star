// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupActor.h"
#include "ManaPickup.generated.h"

/**
 * A randomly spawned pickup that replenish players' mana
 */
UCLASS()
class ITP380_ROCKETTHING_API AManaPickup : public APickupActor
{
	GENERATED_BODY()
	
	AManaPickup();

	virtual void AffectShip(AShip* ShipPlayer);
	
	
};
