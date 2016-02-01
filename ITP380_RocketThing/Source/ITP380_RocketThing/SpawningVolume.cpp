// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Engine.h"
#include "SpawningVolume.h"


// Sets default values
ASpawningVolume::ASpawningVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpawnVolume = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Spawning Volume"));
	RootComponent = SpawnVolume;
}

void ASpawningVolume::BeginPlay(){
	Super::BeginPlay();
	/*for (int k = 0; k < shipsToSpawn.Num(); k++){
		UWorld* World = GetWorld();
		if (World){
			APlayerController* controller = UGameplayStatics::CreatePlayer(World, k, true);
			controller->GetPawn()->Destroy();
			AShip* ship = World->SpawnActor<AShip>(shipsToSpawn[k], FVector::ZeroVector, FRotator::ZeroRotator);
			controller->Possess(ship);
			SpawnShip(ship);
		}
	}*/
}

FVector ASpawningVolume::GetRandomPointInVolume(){
	FVector RandomLocation;
	float MinX, MinY;
	float MaxX, MaxY;
	FVector Origin;
	FVector BoxExtent; 

	Origin = SpawnVolume->Bounds.Origin;
	BoxExtent = SpawnVolume->Bounds.BoxExtent;

	MinX = Origin.X - BoxExtent.X / 2.f;
	MinY = Origin.Y - BoxExtent.Y / 2.f;

	MaxX = Origin.X + BoxExtent.X / 2.f;
	MaxY = Origin.Y + BoxExtent.Y / 2.f;

	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	//--------------------------------This is bad, we need some way to have a variable that says what Z value our game is going to be in
	RandomLocation.Z = 200;
	return RandomLocation;
}

void ASpawningVolume::SpawnShip(AShip* ShipToSpawn){
	FVector PossibleSpawnPoint;
	UWorld* World = GetWorld();
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.bFindInitialOverlaps = true; 
	PossibleSpawnPoint = GetRandomPointInVolume();
	ShipToSpawn->SetActorLocation(PossibleSpawnPoint);
	
}

FVector ASpawningVolume::returnRandomLocation()
{
	FVector PossibleSpawnPoint;
	UWorld* World = GetWorld();
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.bFindInitialOverlaps = true;
	if (World){
		do{
			PossibleSpawnPoint = GetRandomPointInVolume();
			if (!World->LineTraceSingle(HitResult, PossibleSpawnPoint, FVector(PossibleSpawnPoint.X, PossibleSpawnPoint.Y, -100), Params, FCollisionObjectQueryParams())){
				break;
			}
			AActor* Actor = HitResult.Actor.Get();
			FString name = Actor->GetActorLabel();
		} while (!HitResult.Actor.Get()->GetActorLabel().StartsWith("Floor"));
	}
	return PossibleSpawnPoint;
}
