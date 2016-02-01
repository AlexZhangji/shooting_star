// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "Ship.h"
#include "DynamicCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API ADynamicCameraActor : public ACameraActor
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = Camera)
		float BorderSpacing = 500;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float movementSpeed = 1000;

	float YDistance;

	TArray<AShip*> players;
	virtual void Tick(float DeltaSeconds);
	virtual void BeginPlay();
	TPair<float, FVector> GetCenterPosition();
	float CalculateZValue(float desiredY);
	FVector GetDesiredPosition();
	float calculateBuffer();

private:
	bool firstUpdate = true;
};
