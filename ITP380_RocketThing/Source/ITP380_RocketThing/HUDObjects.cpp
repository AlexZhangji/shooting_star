// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "HUDObjects.h"
#include "ITP380_RocketThingPawn.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"


AHUDObjects::AHUDObjects(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// Use the RobotoDistanceField font from the Engine.
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
		
	//timer for random events

	//	list of event string 
	EventsList.Add("Mewtwo Strikes Back");
	EventsList.Add("A Wild Worm Hole Appears");
	EventsList.Add("Ur Dominos is Arriving");
	EventsList.Add("Treasure Box Somewhere");
	EventsList.Add("Something Something Good");
	EventsList.Add("Something Something Bad");
}


void AHUDObjects::DrawHUD()
{
	
	//GetWorld()->GetTimerManager().SetTimer(this, &AHUDObjects::EventHud, 5.f, true);

	// Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	// Call to the parent versions of DrawHUD
	Super::DrawHUD();

	// Get the character and print its current health.
	AITP380_RocketThingPawn* MyHuiji = Cast<AITP380_RocketThingPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	//disable for now.
	//float numHealth = MyHuiji->Health;
	
	float numHealth = 77.f; //placeholder
	float MaxHealth = 100.f;

	if (MyHuiji != NULL)
	{
		// Create a variable for storing the size of printing Game Over.
		FVector2D healthBarSize;

		//health bar code		
		float healthPercent = numHealth / MaxHealth;

		if (numHealth >= 60)DrawRect(FColor::Green, (ScreenDimensions.X - 40.f) / 2.f, (ScreenDimensions.Y - 135.f) / 2.f,
			healthPercent * 80, 7.f);

		else if (numHealth >= 30 && numHealth < 60)DrawRect(FColor::Yellow, (ScreenDimensions.X - 40.f) / 2.f, (ScreenDimensions.Y - 135.f) / 2.f,
			healthPercent * 80, 7.f);

		else if (numHealth < 30)DrawRect(FColor::Red, (ScreenDimensions.X - 40.f) / 2.f, (ScreenDimensions.Y - 135.f) / 2.f,
			healthPercent * 80, 7.f);
		//end of health bar

	
		int powerLevel = 9001;
		
		FString powerStr = "PowerLevel : " + FString::FromInt(9001);;
			DrawText(powerStr, FColor::Red, (ScreenDimensions.X - 250.f), (ScreenDimensions.Y - 60.f), HUDFont);
			
		int numLifes = 9;
		FString lifeStr = "Reincarnation times : " + FString::FromInt(numLifes);
		DrawText(lifeStr, FColor::Yellow, (ScreenDimensions.X - 250.f), (ScreenDimensions.Y - 30.f), HUDFont);
	

		if (MyHuiji->GetActorLocation().X < 400)
		{				
			int timeRand = FMath::RandRange(0, 5)+1;

			if (timeRand < 6 && active)
			{
				FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);


				NotifStr = EventsList[timeRand];

				//DrawText(note, FColor::Red, (ScreenDimensions.X - note.Len()* 30.f) / 2.f, (ScreenDimensions.Y - 535.f) / 2.f, HUDFont, 3.f, false);
			}
			DrawText(NotifStr, FColor::Red, (ScreenDimensions.X - NotifStr.Len()* 30.f) / 2.f, (ScreenDimensions.Y - 535.f) / 2.f, HUDFont, 3.f, false);
			active = false;
		}
		else {
			NotifStr = "";
			active = true;
		}


	}



}



void AHUDObjects::EventHud(){
	

	int timeRand = FMath::RandRange(0, 10);
	
	if (timeRand < 5 && active)
	{
		FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
		

		FString note = EventsList[timeRand];
		DrawText(note, FColor::Red, (ScreenDimensions.X - note.Len()* 30.f) / 2.f, (ScreenDimensions.Y - 535.f) / 2.f, HUDFont, 3.f, false);
	}

}