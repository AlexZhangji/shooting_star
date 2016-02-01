// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "RocketProjectile.h"
#include "Ship.h"
#include "RocketBarrage.h"

void ARocketBarrage::FireFunction(){
	curFireDirection = GetActorForwardVector();
	UWorld* const World = GetWorld();
	FireCluster();
	if (FireSound != nullptr)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}


}

void ARocketBarrage::FireCluster(){
	UWorld* const World = GetWorld();
	for (int k = 0; k < NumFiredAtOnce; k++){
		FRotator FireRotation = curFireDirection.Rotation();
		FRotator randRotation = FRotator(FireRotation.Pitch, FireRotation.Yaw + FMath::RandRange(-startingAngles, startingAngles), FireRotation.Roll);
		// Spawn projectile at an offset from this pawn
		//const FVector SpawnLocation = GetActorLocation() + randRotation.RotateVector(GunOffset);

		if (World != NULL)
		{
			// spawn the projectile
			FVector SpawnLocation = GetActorLocation();
			ARocketProjectile* projectile = World->SpawnActor<ARocketProjectile>(firedObject, SpawnLocation, randRotation);
			AFirable* firable = Cast<AFirable>(projectile);
			firable->Instigator = Owner->GetController();
			firable->SetupOverlap();
			projectile->targetDirection = FireRotation.Vector();
			projectile->Damage = damage;
			firable->SetColor(ProjectileColor);
			firable->OwnerID = OwnerShipNumber;
		}

		//bCanFire = false;

		// try and play the sound if specified
	
	}
	projectilesFired += NumFiredAtOnce;

	if (projectilesFired < NumFiredTotal)
		World->GetTimerManager().SetTimer(TimerHandle_BarrageIntervalExpired, this, &ARocketBarrage::FireCluster, pauseBetweenFires);
	else
		projectilesFired = 0;
}


