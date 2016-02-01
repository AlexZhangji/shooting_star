// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ITP380_RocketThing.h"
#include "ITP380_RocketThingGameMode.h"
#include "ITP380_RocketThingPawn.h"
#include "HUDObjects.h"

AITP380_RocketThingGameMode::AITP380_RocketThingGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our character class
	DefaultPawnClass = AITP380_RocketThingPawn::StaticClass();
		


	//HUD thing
	HUDClass = AHUDObjects::StaticClass();

}