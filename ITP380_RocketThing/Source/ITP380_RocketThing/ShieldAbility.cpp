// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "ShieldAbility.h"

AShieldAbility::AShieldAbility(const FObjectInitializer& ObjectInitializer)
{
	ShieldSphere = CreateDefaultSubobject<UStaticMeshComponent>("Shield Mesh");
	RootComponent = ShieldSphere;
	ShieldSphere->SetVisibility(false);
	ShieldSphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

float AShieldAbility::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	shieldHealth -= Damage;
	if (shieldHealth <= 0)
		StopAbility();
	return Damage;
}


void AShieldAbility::StartAbility(){
	if (ShieldSphere->IsVisible()){
		ShieldSphere->SetVisibility(false);
		ShieldSphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		UGameplayStatics::PlaySoundAttached(ShieldDeactivateSound, owner->ShipMeshComponent);
	}
	else{
		shieldHealth = startingShieldHealth;
		ShieldSphere->SetVisibility(true);
		ShieldSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		UAudioComponent* shieldSound;
		shieldSound = UGameplayStatics::PlaySoundAttached(AbilitySound, owner->ShipMeshComponent);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShieldTimeout, this, &AShieldAbility::turnOffShield, 7.0f);
	}
}

void AShieldAbility::StopAbility(){

}

void AShieldAbility::turnOffShield(){
	if (ShieldSphere->IsVisible()){
		ShieldSphere->SetVisibility(false);
		ShieldSphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		UGameplayStatics::PlaySoundAttached(ShieldDeactivateSound, owner->ShipMeshComponent);
	}
}