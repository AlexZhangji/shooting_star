// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "MachineGun.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API AMachineGun : public AWeapon
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = Damage)
		float FireAngle = 30;

	virtual void FireFunction();
	virtual void Reload();
	
	
};
