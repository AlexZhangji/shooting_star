// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "RocketBarrage.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API ARocketBarrage : public AWeapon
{
	GENERATED_BODY()

	virtual void FireFunction() override;

	FVector curFireDirection;
	void FireCluster();

	float projectilesFired = 0;
	
	//manuallly set damage to 5 in blueprint, in order to get the damage for rocketProjectile.

public:

		UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
		float NumFiredAtOnce;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
		float NumFiredTotal;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
		float pauseBetweenFires;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		float startingAngles = 45;

	

private:
	FTimerHandle TimerHandle_BarrageIntervalExpired;
	
	
};
