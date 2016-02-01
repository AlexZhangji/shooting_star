// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Ability.h"


// Sets default values
AAbility::AAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	bCoolDown = false;
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbility::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAbility::StartAbility(){
}

void AAbility::StopAbility(){
}

void AAbility::InCoolDown(){ bCoolDown = false; }