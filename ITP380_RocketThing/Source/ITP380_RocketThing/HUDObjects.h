// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HUDObjects.generated.h"

/**
 * 
 */
UCLASS()
class ITP380_ROCKETTHING_API AHUDObjects : public AHUD
{
	GENERATED_UCLASS_BODY()


public:			

	UPROPERTY()
		UFont* HUDFont;

	float timerDur = 7.f;
	virtual void DrawHUD() override;
	void EventHud();
	void TimerInvoker();
	bool active = true;
	FString NotifStr = "";

	TArray<FString> EventsList;
};
