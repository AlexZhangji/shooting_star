// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawningVolume.h"
#include "SpawnManager.generated.h"

class ASpawningVolume;
UCLASS()
class ITP380_ROCKETTHING_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// for spawning in a random location
	// this is the problem
	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadWrite)
		ASpawningVolume* MySpawningVolume;

	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadWrite)
		float lowerSpawnDelay = 500;

	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadWrite)
		float upperSpawnDelay = 1000;

	float currentSpawnDelay;

	float timer;

	FTimerHandle TimerHandle;

	// to spawn anything
	void SpawnSomething();

	//// what to spawn
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	//	TSubclassOf<AActor> WhatToSpawn1;

	// what to spawn list
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		TArray<TSubclassOf<AActor>> SpawnTypeLists;
};
