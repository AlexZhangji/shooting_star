// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "BlinkAbility.h"

void ABlinkAbility::StartAbility()
{

	float ManaCost = 20;
	float CoolDown = 5;
	float curMana = owner->getMana();

	if (curMana - ManaCost >= 0 && !(owner->getbCDBlink()))
	{
		owner->setMana(curMana - ManaCost);
		//owner->BlinkInCD();
		bCoolDown = true;

		GetWorld()->GetTimerManager().SetTimer(CDHandle_Ability, this, &ABlinkAbility::callCoolDown, CoolDown);
		if (AbilitySound && AbilityFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX, GetActorLocation());
			UGameplayStatics::PlaySoundAttached(AbilitySound, owner->ShipMeshComponent);
		}

		FRotator curFacing = GetActorRotation();
		FVector curLoc = GetActorLocation();

		//get facing 
		FVector destLoc = curLoc + curFacing.Vector() * 700;
		owner->TeleportTo(destLoc, curFacing);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX, GetActorLocation());
	}
}

void ABlinkAbility::StopAbility(){
}

void ABlinkAbility::callCoolDown()
{
	bCoolDown = false;
	//owner->BlinkInCD();
}