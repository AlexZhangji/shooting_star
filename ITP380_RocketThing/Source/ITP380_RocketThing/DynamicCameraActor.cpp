// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "DynamicCameraActor.h"

void ADynamicCameraActor::BeginPlay(){
	
}

FVector ADynamicCameraActor::GetDesiredPosition(){
	TPair <float, FVector> averagedCenter = GetCenterPosition();
	averagedCenter.Value.Z = CalculateZValue(averagedCenter.Key + BorderSpacing +  200);
	return averagedCenter.Value;
}

void ADynamicCameraActor::Tick(float DeltaSeconds){
	if (true){
		firstUpdate = false;
		UWorld* world = GetWorld();
		players = TArray<AShip*>();
		if (world){
			//get a reference to all of the player pawns
			int index = 0;
			while (true){
				APawn* currentPawn = UGameplayStatics::GetPlayerPawn(world, index);
				if (currentPawn){
					++index;
					players.Add(Cast<AShip>(currentPawn));
				}
				else{
					break;
				}
			}
		}

		FVector pos = GetDesiredPosition();
		float distTo = FVector::Dist(GetActorLocation(), pos);
		float timeToArrive = distTo / movementSpeed;
<<<<<<< HEAD
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), pos, DeltaSeconds/.5f, 1));
=======
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), pos, DeltaSeconds / .5f, 1));
	}
	else{
		
>>>>>>> refs/remotes/origin/master
		//SetActorLocation(pos);
	}
}

float ADynamicCameraActor::calculateBuffer(){
	float maxBuffer = 0;
	float maxX = YDistance * CameraComponent->AspectRatio;
	FVector myPos = GetActorLocation();
	for (AShip* pawn : players){
		FVector pos = pawn->GetActorLocation();
		float xDif = (pos.X - myPos.X);
		float yDif = (pos.Y - myPos.Y);
		
		float xDistanceFromBorder = maxX - FMath::Abs(xDif);
		float yDistanceFromBorder = YDistance - FMath::Abs(yDif);
		FVector vel = pawn->ShipMeshComponent->GetPhysicsLinearVelocity();
		float xBuffer=0,yBuffer=0;
		if (xDif < 0 && vel.X < 0){
			xBuffer = FMath::Max(xBuffer,xDistanceFromBorder + vel.X);
		}
		if (xDif > 0 && vel.X>0){
			xBuffer = FMath::Max(xBuffer, xDistanceFromBorder - vel.X);
		}
		if (yDif < 0 && vel.Y < 0){
			yBuffer = FMath::Max(yBuffer, yDistanceFromBorder + vel.Y);
		}
		if (yDif > 0 && vel.Y > 0){
			yBuffer = FMath::Max(yBuffer, yDistanceFromBorder - vel.Y);
		}
		maxBuffer = FMath::Max(maxBuffer, yBuffer);
		maxBuffer = FMath::Max(maxBuffer, xBuffer);
	}
	return maxBuffer;
}

float ADynamicCameraActor::CalculateZValue(float desiredY){
	return desiredY / FMath::Tan(CameraComponent->FieldOfView / 2)* 3;
}

TPair<float, FVector> ADynamicCameraActor::GetCenterPosition(){
	float maxX = INT_MIN, maxY = INT_MIN, minX = INT_MAX, minY = INT_MAX;
	for (int k = 0; k < players.Num(); k++){
		FVector location = players[k]->GetActorLocation();
		maxX = FMath::Max(location.X, maxX);
		maxY = FMath::Max(location.Y, maxY);
		minX = FMath::Min(location.X, minX);
		minY = FMath::Min(location.Y, minY);
	}
	FVector middlePosition = FVector((minX+maxX)/2, (minY+maxY)/2, 200);
	float maxDistance = FMath::Max((maxX - minX) / 2, (maxY - minY) / CameraComponent->AspectRatio / 2);
	TPair<float, FVector> result;
	result.Key = maxDistance;
	result.Value = middlePosition;
	YDistance = maxDistance;
	return result;
}



