// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability.h"
#include "BlinkAbility.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API ABlinkAbility : public AAbility
{
	GENERATED_BODY()

	virtual void StartAbility() override;

	virtual void StopAbility() override;
	
	void callCoolDown();
};
