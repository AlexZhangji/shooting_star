// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Engine.h"
#include "SpawnManager.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnManager::SpawnSomething, FMath::FRandRange(lowerSpawnDelay, upperSpawnDelay));
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	/*
	Super::Tick(DeltaTime);
	timer += DeltaTime;
	if (this->timer >= 300){
	// a 1 in 2 chance
	int randNum = rand() % 2;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(randNum));
	if (randNum == 1){
	this->SpawnSomething();
	this->timer = 0;
	}
	else{
	this->timer = 0;
	}
	}*/
}

void ASpawnManager::SpawnSomething()
{
	UWorld* World = GetWorld();
	if (World){
		// get spawn point
		FVector SpawnPoint = MySpawningVolume->returnRandomLocation();
		SpawnPoint.Z = 0;
		// get spawn type
		int size = SpawnTypeLists.Num();
		int index = rand() % size;
		TSubclassOf<AActor> WhatToSpawn = SpawnTypeLists[index];
		// Set the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Get a random rotation for the spawned item
		FRotator SpawnRotation(90.f, 0.0f, 0.0f);

		if (WhatToSpawn){
			// spawn the health pack
			AActor* const SpawnedHealthPack = World->SpawnActor<AActor>(
				WhatToSpawn, SpawnPoint, SpawnRotation, SpawnParams);
		}
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnManager::SpawnSomething, FMath::FRandRange(lowerSpawnDelay, upperSpawnDelay));
	}
}

