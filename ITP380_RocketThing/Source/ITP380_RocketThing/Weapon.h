// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AShip;

UCLASS()
class ITP380_ROCKETTHING_API AWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	FTimerHandle TimerHandle_ShotIntervalExpired;
	virtual void Reload();
	bool bCanFire;
	bool bIsFiring;
	float intervalBetweenFire;

public:	
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);

	virtual void Fire();

	void setOwnerNum(int i);

	void Initialize(AShip* owner);

	//function that gets called inside fire after we check that we can actually fire
	//override this to do your actual firing pls
	virtual void FireFunction();

	virtual FName GetProjectileName();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void StopFire();


	AShip* Owner;

	FLinearColor ProjectileColor = FColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Owner")
		int32 OwnerShipNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Appearance")
		UStaticMeshComponent*  WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Appearance")
		UStaticMeshComponent* firePoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float FireRate;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	//void setAllColor(AFirable* firable);

	void SetProjectileColor(FLinearColor color);

	//this is object that gets spawned when we fire
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<AActor> firedObject;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundBase* WeaponSoundEffect;
	
	
};
