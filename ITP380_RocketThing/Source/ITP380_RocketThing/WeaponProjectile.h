// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Firable.h"
#include "WeaponProjectile.generated.h"

UCLASS(config = Game)
class AWeaponProjectile : public AFirable
{
	GENERATED_BODY()

public:
	AWeaponProjectile(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
		float StartSpeed;

	virtual void BeginPlay() override;
};

