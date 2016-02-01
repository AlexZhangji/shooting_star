// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "PickupActor.h"


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnHit);
	if (SpawnParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, GetActorLocation(), GetActorRotation());

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_pickup, this, &APickupActor::destoryA, 15.f);
}

//destory actor when need
void APickupActor::destoryA()
{
	if (DeathParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation());
	this->Destroy();
}

// Called every frame
void APickupActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APickupActor::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		AShip* ShipPlayer = Cast<AShip>(OtherActor);
		if (ShipPlayer)
		{
			AffectShip(ShipPlayer);
			if (consumeSound)
				UGameplayStatics::PlaySoundAtLocation(this, consumeSound, GetActorLocation());
			if (DeathParticle)
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation());
			Destroy();
		}
	}
}

void APickupActor::AffectShip(AShip* ShipPlayer){

}

