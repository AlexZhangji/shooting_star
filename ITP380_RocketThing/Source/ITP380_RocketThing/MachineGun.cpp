// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "WeaponProjectile.h"
#include "Ship.h"
#include "MachineGun.h"

void AMachineGun::FireFunction(){
	UWorld* World = GetWorld();
	if (World){
		FVector SpawnLocation = GetActorLocation();
		FRotator FireRotation = GetActorRotation();
		FRotator randRotation = FRotator(FireRotation.Pitch, FireRotation.Yaw + FMath::RandRange(-FireAngle, FireAngle), FireRotation.Roll);
		AWeaponProjectile* projectile = World->SpawnActor<AWeaponProjectile>(firedObject, SpawnLocation, randRotation);
		AFirable* firable = Cast<AFirable>(projectile);
		firable->Instigator = Owner->GetController();
		firable->SetupOverlap();
		firable->Damage = damage;
		//firable->SetColor(ProjectileColor);

		firable->OwnerID = OwnerShipNumber;
	}
}

void AMachineGun::Reload(){
    if (bIsFiring){
		bCanFire = true;
		Fire();
	}
	else{
		bCanFire = true;
	}

}