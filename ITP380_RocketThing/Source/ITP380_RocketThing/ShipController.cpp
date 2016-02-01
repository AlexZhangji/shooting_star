// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Ability.h"
#include "ShipController.h"

enum FireModes{
	StandardFire,
	StopFire
};

AShipController::AShipController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bAutoManageActiveCameraTarget = false;
	bForceFeedbackEnabled = true;
}	

void AShipController::SetupInputComponent(){
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AShipController::MoveInXAxis);
	InputComponent->BindAxis("MoveRight", this, &AShipController::MoveInYAxis);
	InputComponent->BindAxis("FaceForward", this, &AShipController::RotateInYAxis);
	InputComponent->BindAxis("FaceRight", this, &AShipController::RotateInXAxis);
	InputComponent->BindAction("FirePrimary",IE_Pressed,this, &AShipController::StartPawnFire);
	InputComponent->BindAction("FirePrimary", IE_Released, this, &AShipController::StopPawnFire);
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &AShipController::SwapPawnWeaponNext);
<<<<<<< HEAD
	InputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AShipController::SwapPawnWeaponPrevious);
	InputComponent->BindAction("FirstSpecialAbility", IE_Pressed, this, &AShipController::ActivatePrimaryAbility);
	InputComponent->BindAction("FirstSpecialAbility", IE_Released, this, &AShipController::DeactivatePrimaryAbility);
	InputComponent->BindAction("SecondSpecialAbility", IE_Pressed, this, &AShipController::ActivateSecondaryAbility);
	InputComponent->BindAction("SecondSpecialAbility", IE_Pressed, this, &AShipController::DeactivateSecondaryAbility);
=======
	InputComponent->BindAction("UseFirstAbility", IE_Pressed, this, &AShipController::ActivatePrimaryAbility);
	InputComponent->BindAction("UseFirstAbility", IE_Released, this, &AShipController::DeactivatePrimaryAbility);
	InputComponent->BindAction("UseSecondAbility", IE_Pressed, this, &AShipController::ActivateSecondaryAbility);
	InputComponent->BindAction("UseSecondAbility", IE_Pressed, this, &AShipController::DeactivateSecondaryAbility);
>>>>>>> refs/remotes/origin/master

	//Abilities
	/*
	InputComponent->BindAction("ActivateShield", IE_Pressed, this, &AShipController::ActivateShield);
	InputComponent->BindAction("Blinking", IE_DoubleClick, this, &AShipController::Blinking);
	InputComponent->BindAction("Rewind", IE_DoubleClick, this, &AShipController::Rewind);
	InputComponent->BindAction("TripleBlink", IE_DoubleClick, this, &AShipController::TripleBlink);
	InputComponent->BindAction("HomingMissle", IE_DoubleClick, this, &AShipController::HomingMissle);
	InputComponent->BindAction("Berserk", IE_DoubleClick, this, &AShipController::Berserk);*/
}

void AShipController::MoveInXAxis(float value){
	APawn* pawn = GetPawn();
	if (pawn){
		pawn->AddMovementInput(FVector(1, 0, 0),value);
	}
}

void AShipController::MoveInYAxis(float value){
	APawn* pawn = GetPawn();
	if (pawn){
		pawn->AddMovementInput(FVector(0, 1, 0),value);
	}
}

void AShipController::StartPawnFire(){
	APawn* pawn = GetPawn();
	if (pawn){
		pawn->PawnStartFire(FireModes::StandardFire);
	}
}

void AShipController::StopPawnFire(){
	APawn* pawn = GetPawn();
	if (pawn){
		pawn->PawnStartFire(FireModes::StopFire);
	}
}

void AShipController::SwapPawnWeaponNext(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->SwitchWeapon(1);
	}
}

void AShipController::SwapPawnWeaponPrevious(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->SwitchWeapon(-1);
	}
}

void AShipController::ActivatePrimaryAbility(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
<<<<<<< HEAD
		shipPawn->AbilityList[0]->StartAbility();
=======
		shipPawn->useFirstAbility();
>>>>>>> refs/remotes/origin/master
	}
}

void AShipController::DeactivatePrimaryAbility(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
<<<<<<< HEAD
		shipPawn->AbilityList[0]->StopAbility();
=======
>>>>>>> refs/remotes/origin/master
	}
}

void AShipController::ActivateSecondaryAbility(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
<<<<<<< HEAD
		shipPawn->AbilityList[1]->StartAbility();
=======
		shipPawn->useSecondAbility();
>>>>>>> refs/remotes/origin/master
	}
}

void AShipController::DeactivateSecondaryAbility(){
		APawn* pawn = GetPawn();
		if (pawn){
			AShip* shipPawn = Cast<AShip>(pawn);
			shipPawn->AbilityList[1]->StopAbility();
	}
}

void AShipController::RotateInXAxis(float value){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->YFacing = value;
	}
}

void AShipController::RotateInYAxis(float value){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->XFacing = value;
	}
}

void AShipController::ActivateShield(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->ActivateShiled();
	}
}

void AShipController::DeactivateShield(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->DeactivateShield();
	}
}

void AShipController::Blinking(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->Blink();
	}
}

void AShipController::Rewind(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->Rewind();
	}
}

void AShipController::TripleBlink(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->TripleBlink();
	}
}

void AShipController::HomingMissle(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->homingMissle();
	}
}

void AShipController::Berserk(){
	APawn* pawn = GetPawn();
	if (pawn){
		AShip* shipPawn = Cast<AShip>(pawn);
		shipPawn->Berserk();
	}
}