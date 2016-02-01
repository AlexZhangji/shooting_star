// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "HealthPackActor.h"
#include "Ship.h"
#include "SpawningVolume.h"

// Sets default values
AHealthPackActor::AHealthPackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthBoost = 20.f;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health Pack Mesh"));
	RootComponent = PickupMesh;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AHealthPackActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHealthPackActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called when overlapped by a ship
void AHealthPackActor::SetupOverlap()
{
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPackActor::OnHit);
}

/*
void AHealthPackActor::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		AShip* ShipPlayer = Cast<AShip>(OtherActor);
		if (ShipPlayer)
		{
			ShipPlayer->ConsumeHealthPack(this->HealthBoost);
			this->Destroy();
		}
	}
}*/

void AHealthPackActor::AffectShip(AShip* ShipPlayer){
	ShipPlayer->ConsumeHealthPack(this->HealthBoost);
}