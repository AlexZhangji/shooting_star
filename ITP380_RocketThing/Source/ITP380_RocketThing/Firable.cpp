// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Firable.h"
#include "Ship.h"
#include "ShieldAbility.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFirable::AFirable(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	// Create mesh component for the projectile sphere
	FirableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	FirableMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	FirableMesh->AttachTo(RootComponent);
	FirableMesh->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = FirableMesh;
	PrimaryActorTick.bCanEverTick = true;
	Damage = 5;	
}

void AFirable::SetupOverlap()
{
	FirableMesh->OnComponentBeginOverlap.AddDynamic(this, &AFirable::OnHit);		// set up a notification for when this component hits something
}

// Called when the game starts or when spawned
void AFirable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );



}

void AFirable::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		if (OtherActor->GetClass()->IsChildOf(AShip::StaticClass())){
			AShip* HitShip = Cast<AShip>(OtherActor);
			//Check that i'm not hitting my own ship
			if (HitShip->GetController() != Instigator){
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
 				FDamageEvent DamageEvent = FDamageEvent(ValidDamageTypeClass);
				HitShip->TakeDamage(Damage, DamageEvent, Instigator, Instigator->GetPawn());
				OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
				
				/*
				AShip* ownerShip = Cast<AShip>(Instigator->GetPawn());
				int32 theOwnerID = ownerShip->PlayerNumber;
				if (OwnerID != theOwnerID) OwnerID = theOwnerID;
				*/

				OnDestroyed();
			}
		}
		else if (OtherActor->GetClass()->IsChildOf(AShieldAbility::StaticClass())){
			AShieldAbility* shield = Cast<AShieldAbility>(OtherActor);
			if (shield->owner->GetController() != Instigator){
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent = FDamageEvent(ValidDamageTypeClass);
				shield->TakeDamage(Damage, DamageEvent, Instigator, Instigator->GetPawn());
			}
		}
		else{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
			OnDestroyed();
		}
	}
	else{
		OnDestroyed();
	}
}

void AFirable::OnDestroyed(){

	// play hit effects
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
	Destroy();
}

void AFirable::SetColor(FLinearColor col){
	UMaterialInstanceDynamic* material = FirableMesh->CreateDynamicMaterialInstance(0);
	material->SetVectorParameterValue("Color", col);
	/*TArray<UActorComponent*> particles = GetComponentsByClass(TSubclassOf<UParticleSystemComponent>());
	for (UActorComponent* comp : particles){
		UParticleSystemComponent* ParticleComponent = Cast<UParticleSystemComponent>(comp);
		if (ParticleComponent){

		}
	}*/
}



