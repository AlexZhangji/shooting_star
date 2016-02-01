// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ship.h"
#include "Ability.generated.h"

UCLASS()
class ITP380_ROCKETTHING_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		UParticleSystem* AbilityFX;

	UPROPERTY(Category = Sound, EditDefaultsOnly)
		USoundBase* AbilitySound;

	// Sets default values for this actor's properties
	AAbility();

	AShip* owner;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void StartAbility();

	virtual void StopAbility();

	FTimerHandle CDHandle_Ability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bCoolDown;

	void InCoolDown();

	
};
