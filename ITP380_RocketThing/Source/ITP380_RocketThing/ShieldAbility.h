// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability.h"
#include "ShieldAbility.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API AShieldAbility : public AAbility
{
	GENERATED_BODY()

		float shieldHealth;

	FTimerHandle TimerHandle_ShieldTimeout;

		AShieldAbility(const FObjectInitializer& ObjectInitializer);

		UPROPERTY(EditDefaultsOnly, Category = Health)
			float startingShieldHealth;

		UPROPERTY(EditDefaultsOnly, Category = Effects)
			USoundBase* ShieldDeactivateSound;

		UPROPERTY(VisibleAnywhere, Category = Effects)
		UStaticMeshComponent* ShieldSphere;

	virtual void StartAbility() override;

	virtual void StopAbility() override;

	void turnOffShield();

public:
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	
	
};
