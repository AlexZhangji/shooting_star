// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ship.h"
#include "PickupActor.generated.h"

UCLASS()
class ITP380_ROCKETTHING_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void destoryA();//destory actor when need

	FTimerHandle TimerHandle_pickup;
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Appearance)
		UStaticMeshComponent* PickupMesh;

	// handles collision with other mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Physics)
		USphereComponent* SphereCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		USoundBase* consumeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Appearance)
		UParticleSystem* DeathParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Appearance)
		UParticleSystem* SpawnParticle;

	UFUNCTION()
	virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void AffectShip(AShip* Ship);
};
