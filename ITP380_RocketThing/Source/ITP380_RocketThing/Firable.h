// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Firable.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class ITP380_ROCKETTHING_API AFirable : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Appearance, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* FirableMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio)
		USoundBase* explosionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OwnerCate")
		int32 OwnerID;


	// Hit effects migrated from SHMUP. The plan is to only play this
	// when it hits another ship
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Effects) // need blueprint access for dynamic color
		UParticleSystem* HitFX;


	AController* Instigator;

	UFUNCTION()
		virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetupOverlap();

	virtual void OnDestroyed();

	// Sets default values for this actor's properties
	AFirable(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	void SetColor(FLinearColor col);
};
