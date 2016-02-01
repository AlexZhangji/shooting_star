// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponProjectile.h"
#include "RocketProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API ARocketProjectile : public AWeaponProjectile
{
	GENERATED_BODY()

	ARocketProjectile(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;


	/** Projectile movement component */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
		float handling = 5;

	FVector targetDirection;

	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return FirableMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	
};
