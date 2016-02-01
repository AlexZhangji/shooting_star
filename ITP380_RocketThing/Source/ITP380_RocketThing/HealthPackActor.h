// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupActor.h"
#include "HealthPackActor.generated.h"

class ASpawningVolume;

UCLASS()
class ITP380_ROCKETTHING_API AHealthPackActor : public APickupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPackActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called when overlapped by a ship
	void SetupOverlap();

	// Called in SetupOverlap
	//UFUNCTION()
	//virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		//int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** health that a player can get from this health pack */
	UPROPERTY(EditAnywhere, Category = Stats)
		float HealthBoost;

	virtual void AffectShip(AShip* ShipPlayer);
};
