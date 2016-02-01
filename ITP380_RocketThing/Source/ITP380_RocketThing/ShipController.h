// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Ship.h"
#include "ShipController.generated.h"

/**
 * 
 */


UCLASS()
class ITP380_ROCKETTHING_API AShipController : public APlayerController
{
	GENERATED_BODY()

public:
	AShipController(const FObjectInitializer& ObjectInitializer);
	virtual void SetupInputComponent() override;
	

private:
	//variables


	//functions
	void MoveInXAxis(float value);
	void MoveInYAxis(float value);
	void StartPawnFire();
	void StopPawnFire();
	void SwapPawnWeaponNext();
	void SwapPawnWeaponPrevious();
	void RotateInXAxis(float value);
	void RotateInYAxis(float value);

	//added
	void ActivatePrimaryAbility();
	void DeactivatePrimaryAbility();
	void ActivateSecondaryAbility();
	void DeactivateSecondaryAbility();

	void ActivateShield();
	void DeactivateShield();

	void Blinking();
	void Rewind();

	void TripleBlink();
	void HomingMissle();
	void Berserk();

};
