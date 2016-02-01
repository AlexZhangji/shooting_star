// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ship.h"
#include "HealthPackActor.h"
#include "SpawningVolume.generated.h"


UCLASS()
class ITP380_ROCKETTHING_API ASpawningVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	

	ASpawningVolume(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Spawning)
		TArray<TSubclassOf<AShip>> shipsToSpawn;

	UPROPERTY(EditAnywhere, Category = Camera)
		AActor* Camera;

	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
		UBoxComponent* SpawnVolume;

	UFUNCTION(BlueprintCallable, Category = Spawning)
	void SpawnShip(AShip* ShipToSpawn);

	// this point is not guaranteed to be clear on map (something may already be there)
	FVector GetRandomPointInVolume();

	virtual void BeginPlay() override;

	void ReturnPlayerToMap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// return a valid point in the map that can be used to spawn (as contrary to GetRaondomPointInVolume)
	FVector returnRandomLocation();
};
