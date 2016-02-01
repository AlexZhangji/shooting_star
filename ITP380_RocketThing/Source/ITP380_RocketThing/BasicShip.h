// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ship.h"
#include "BasicShip.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API ABasicShip : public AShip
{
	GENERATED_BODY()
	
public:
	bool bIsChargingMovement;
	float MovementCharge;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float MovementChargeTime=3;

    // Sets default values for this pawn's properties
    ABasicShip(const FObjectInitializer& ObjectInitializer);
	
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void StartSpecialMovement();
	virtual void EndSpecialMovement();
	
};
