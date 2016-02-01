// F7ill out your copyright notice in the Description page of Project Settings.


#include "ITP380_RocketThing.h"
#include "Engine.h"
#include "Ship.h"
#include "SpawningVolume.h"
#include "ShipController.h"
#include "HealthPackActor.h"

#include "Ability.h"

void AShip::useFirstAbility(){
	if (firstAbility == AbilityType::Blink){
		this->Blink();
	}
	else if (firstAbility == AbilityType::Beserk){
		this->Berserk();
	}
	else if (firstAbility == AbilityType::Missile){
		this->homingMissle();
	}
	else if (firstAbility == AbilityType::Rewind){
		this->Rewind();
	}
	else if (firstAbility == AbilityType::Shield){
		this->ActivateShiled();
	}
	else if (firstAbility == AbilityType::ShortBlink){
		this->TripleBlink();
	}
	else if (firstAbility == AbilityType::Homing){
		this->homingMissle();
	}
}

void AShip::useSecondAbility(){
	if (secondAbility== AbilityType::Blink){
		this->Blink();
	}
	else if (secondAbility == AbilityType::Beserk){
		this->Berserk();
	}
	else if (secondAbility == AbilityType::Missile){
		this->homingMissle();
	}
	else if (secondAbility == AbilityType::Rewind){
		this->Rewind();
	}
	else if (secondAbility == AbilityType::Shield){
		this->ActivateShiled();
	}
	else if (secondAbility == AbilityType::ShortBlink){
		this->TripleBlink();
	}
	else if (secondAbility == AbilityType::Homing){
		this->homingMissle();
	}
}

bool AShip::firstAbilityOnCooldown(){
	if (firstAbility == AbilityType::Blink){
		return this->bCDBlink;
	}
	else if (firstAbility == AbilityType::Beserk){
		return this->bCDBerserk;
	}
	else if (firstAbility == AbilityType::Missile){
		return this->bCDHoming;
	}
	else if (firstAbility == AbilityType::Rewind){
		return this->bCDRewind;
	}
	else if (firstAbility == AbilityType::Shield){
		return this->bCDShield;
	}
	else if (firstAbility == AbilityType::ShortBlink){
		return this->bCDTripleBlink;
	}
	else if (firstAbility == AbilityType::Homing){
		return bCDHoming;
	}
	else return false;
}

bool AShip::secondAbilityOnCooldown(){
	if (secondAbility == AbilityType::Blink){
		return this->bCDBlink;
	}
	else if (secondAbility == AbilityType::Beserk){
		return this->bCDBerserk;
	}
	else if (secondAbility == AbilityType::Missile){
		return this->bCDHoming;
	}
	else if (secondAbility == AbilityType::Rewind){
		return this->bCDRewind;
	}
	else if (secondAbility == AbilityType::Shield){
		return this->bCDShield;
	}
	else if (secondAbility == AbilityType::ShortBlink){
		return this->bCDTripleBlink;
	}
	else if (secondAbility == AbilityType::Homing){
		return bCDHoming;
	}
	else return false;
}

// Sets default values
AShip::AShip(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	LeftEngine = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftEngine"));
	LeftEngine->AttachTo(RootComponent, "Left Engine");

	RightEngine = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightEngine"));
	RightEngine->AttachTo(RootComponent, "Right Engine");

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));

	bIsDead = false;
	
	//added for deathCount
	alreadyDead = false;
	DeathCount = 0;
	PlayerNumber = 0;
	DefaultWeaponNum = 3;
	ShieldIsOn = 0;
	InitCoolDowns();
	//set up amount of damage shiled will take
	shieldDamage = 50;
	MaxshieldDamage = 50;
	// Movement
	MoveSpeed = 5000.f;

	// initialize arrays
	AllWeapons = TArray<TSubclassOf<AWeapon>>();
	Weapons = TArray<AWeapon*>();
	WeaponIndex = 0;

	//abilities helper var
	bRewindInProcess = false;
	bCanSpawnIlussion = true;
	bHomingInProcess = false;
	bBerserkerInProgress = false;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	//virbration
	
	f.UUID = 1;
	f.CallbackTarget = this;
	//f.ExecutionFunction = "OnFeedbackEnd";

	UWorld* World = GetWorld();
	startingZPosition = GetActorLocation().Z;
	if (World){
		if (Weapons.Num() == 0){
			for (TSubclassOf<AWeapon> WeaponClass : AllWeapons){
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = this;
				AWeapon* MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
				MyWeapon->Initialize(this);
				if (MyWeapon){
					MyWeapon->WeaponMesh->AttachTo(ShipMeshComponent, TEXT("Weapon Point"));
				}
				MyWeapon->SetActorHiddenInGame(true);
				Weapons.Add(MyWeapon);
				MyWeapon->OwnerShipNumber = PlayerNumber;
				//TArray<ASpawningVolume*> result();
				//SpawningVolume = UGameplayStatics::GetAllActorsOfClass(World, TSubclassOf<ASpawningVolume>(),result)[0];

			}
		}
		//resolve multi color weapon problem
		WeaponIndex = 0;
		SelectedWeapon = Weapons[WeaponIndex];
		SelectedWeapon->SetActorHiddenInGame(false);


		
		initAbilityList();//test
	}
	TArray<AActor*> result;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<ASpawningVolume>(), result);
	//SpawningVolume = Cast<ASpawningVolume>(result[0]);
}

void AShip::PawnStartFire(uint8 FireModeNum){
	if (SelectedWeapon){
		if (FireModeNum == 0){
			SelectedWeapon->Fire();
		}
		else if (FireModeNum == 1){
			SelectedWeapon->StopFire();
		}
	}
}



// Called every frame
void AShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector position = GetActorLocation();
	position.Z = startingZPosition;
	SetActorLocation(position);
	FVector movement = ConsumeMovementInputVector();
	Move(movement,DeltaTime);		

	//vib
	AShipController* ThisCont = Cast<AShipController>(this->GetController());
	if (forceFeedbackDamage)
	ThisCont->PlayDynamicForceFeedback(forceFeedbackDamage, 1.1f, true, true, true, true, EDynamicForceFeedbackAction::Update, f);

	//for color change
	if (SelectedWeapon->OwnerShipNumber != PlayerNumber)
		SelectedWeapon->setOwnerNum(PlayerNumber);



	//for death count
	if (!alreadyDead && bIsDead)		
	{
		DeathCount++;
		alreadyDead = true;
	}

	if(Mana+ 0.025 <= 100 )
	Mana += .025;
}

void AShip::Move(FVector input, float DeltaSeconds){
	const float ForwardValue = input.Y;
	const float RightValue = input.X;

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector StickDirection = FVector(RightValue,ForwardValue, 0.f) * MoveSpeed;
	FRotator stickRotation = StickDirection.Rotation();
	FVector curForward = GetVelocity();
	FVector newForward = FVector::ZeroVector;
	float turnMag = DeltaSeconds * GetVelocity().Size() * handling;
	newForward = curForward + FVector(RightValue,ForwardValue, 0.f) * turnMag;
	newForward.ClampMaxSize(curForward.Size());
	ShipMeshComponent->SetPhysicsLinearVelocity(newForward);
	// StickDirection acts as an acceleration vector here
	FVector MoveDirection = StickDirection * DeltaSeconds + ShipMeshComponent->GetPhysicsLinearVelocity();
	MoveDirection = MoveDirection.GetClampedToMaxSize(4000.0f);	// limit speed so it doesn't go crazy
	ShipMeshComponent->SetPhysicsLinearVelocity(MoveDirection);
	Rotate(MoveDirection, DeltaSeconds);
}

void AShip::Rotate(FVector MoveDirection, float DeltaSeconds){
	// Calculate rotation
	if (XFacing==0&&YFacing==0){
		MoveDirection.Normalize();
		FRotator rRotation = MoveDirection.Rotation();
		FRotator curRotation = GetActorRotation();
		FRotator result = FMath::RInterpTo(curRotation, rRotation, DeltaSeconds, RotationSpeed);
		result.Pitch = 0;
		RootComponent->SetWorldRotation(result);
	}
	else{
		FVector desiredDirection = FVector(XFacing, YFacing, 0);
		FRotator desiredRotation = desiredDirection.Rotation();
		FRotator result = FMath::RInterpTo(GetActorRotation(), desiredRotation, DeltaSeconds, RotationSpeed);
		result.Pitch = 0;
		RootComponent->SetWorldRotation(result);
	}
}

float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Damage;//Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	bool CauserInBerserk = false;
	AShip* otherShip = Cast<AShip>(EventInstigator->GetPawn());

	//vibration fx
	if (this->GetController())
	{
		AShipController* ThisCont = Cast<AShipController>(this->GetController());
		ThisCont->PlayDynamicForceFeedback(Damage / 15, 1.1f, true, true, true, true, EDynamicForceFeedbackAction::Start, f);
		forceFeedbackDamage = Damage/15;
	}

	if (otherShip)
	{
 		if (otherShip->bBerserkerInProgress) CauserInBerserk = true;
	}
	//under BerserkMode more damage will be apply
	if (bBerserkerInProgress || CauserInBerserk)
		ActualDamage = 1.5*Damage;

	if (!bIsDead && ActualDamage > 0.0f)
	{
		if (ShieldIsOn == 0)
		{
			health -= ActualDamage;
			if (health <= 0.0f)
			{
<<<<<<< HEAD
				//Cast<AShip>(DamageCauser)->score++; //crash?
				DeathCount++;
=======
				Cast<AShip>(DamageCauser)->score++; //crash?
>>>>>>> refs/remotes/origin/master
				ProcessDeath();
			}
		}
		else //when shield is activated
		{
			shieldDamage -= ActualDamage;		
			if (shieldDamage <= 0) DeactivateShield();
			}	
    }

     return ActualDamage;
}

void AShip::ProcessDeath(){
	APlayerController* Controller = Cast<APlayerController>(GetController());
	bIsDead = true;
	SelectedWeapon->StopFire();
	PlayRequiem();

	//complete death process
	bCanBeDamaged = false;

	// play hit effects
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
	
	//set invisible for 3sec
	SetActorHiddenInGame(true);

	//currently not truly destroy ship
	//Destroy();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Respawn, this, &AShip::RespawnShip, 3.0f);
	Controller->DisableInput(Controller);
	
	bRewindInProcess = false;
}

void AShip::RespawnShip()
{
	//set visible and "rebirth"
	APlayerController* Controller = Cast<APlayerController>(GetController());
	Controller->EnableInput(Controller);
	SetActorHiddenInGame(false);
	health = MaxHealth;
	Mana = MaxMana;
	bIsDead = false;
	alreadyDead = false;
	bCanBeDamaged = true;
	if (SpawningVolume)
		SpawningVolume->SpawnShip(this);

	InitCoolDowns();
}

void AShip::SwitchWeapon(int increment){

	if (increment == 1)
	UGameplayStatics::PlaySoundAttached(MiscSound[0], this->ShipMeshComponent);

	if (increment == -1)
	UGameplayStatics::PlaySoundAttached(MiscSound[1], this->ShipMeshComponent);

	
	WeaponIndex += increment;
	
	if (WeaponIndex > Weapons.Num()-1){ //3 is number of weapon a ship is set to have.
		WeaponIndex = 0;
	}
	else if (WeaponIndex < 0){
		WeaponIndex = Weapons.Num() - 1;
	}
	SelectedWeapon->SetActorHiddenInGame(true);
	SelectedWeapon->StopFire();
	SelectedWeapon = Weapons[WeaponIndex];
	SelectedWeapon->SetActorHiddenInGame(false);
}


void AShip::StartAbility(){
	if (Ability)
		Ability->StartAbility();
}

void AShip::EndAbility(){
	if (Ability)
		Ability->StopAbility();
}

void AShip::SetPlayerIDAndColor(int32 ID, FLinearColor col){
	PlayerNumber = ID;
	PointLight->SetLightColor(col);
	for (TSubclassOf<AWeapon> WeaponClass : AllWeapons){
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		AWeapon* MyWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		MyWeapon->Initialize(this);
		if (MyWeapon){
			MyWeapon->WeaponMesh->AttachTo(ShipMeshComponent, TEXT("Weapon Point"));
		}
		MyWeapon->SetActorHiddenInGame(true);
		Weapons.Add(MyWeapon);
		//TArray<ASpawningVolume*> result();
		//SpawningVolume = UGameplayStatics::GetAllActorsOfClass(World, TSubclassOf<ASpawningVolume>(),result)[0];

	}
	for (AWeapon* weapon : Weapons){
		weapon->SetProjectileColor(col);
	}
}



/*
void AShip::StartSpecialMovement(){
	
}

void AShip::EndSpecialMovement(){

}*/

//play sound according to death count
void AShip::PlayRequiem()
{
	if (DeathCount < 5){
		if (mySound[DeathCount])
		{
			UGameplayStatics::PlaySoundAttached(mySound[DeathCount], this->ShipMeshComponent);
		}
	}
	else
		UGameplayStatics::PlaySoundAttached(mySound[FMath::FRandRange(4, 8)], this->ShipMeshComponent);
}

// Called when the ship gets into range of a HealthPack
void AShip::ConsumeHealthPack(float HealthBoost)
{
	if (!bIsDead && HealthBoost > 0.0f)
	{
		this->health += HealthBoost;
	}
}

void AShip::ActivateShiled()
{
	float ManaCost = 30;
	float CoolDown = 15;
	
	if (ShieldIsOn == 1){
		DeactivateShield();
	}
	else{
		if (Mana - ManaCost >= 0 && !bCDShield)
		{
			if (ShieldIsOn == 0)
			{
				Mana -= ManaCost;
				bCDShield = true;

				GetWorld()->GetTimerManager().SetTimer(CDHandle_Shield, this, &AShip::ShiledInCD, CoolDown);


				ShieldIsOn = 1;
				
				ShiledSound = UGameplayStatics::PlaySoundAttached(AbilitySound[1], this->ShipMeshComponent);
				ShiledSound->Play();
				//PlaySoundOnActor(AbilitySound[1], 1.f, 1.f);// HOW DO I STOP THIS?
				shieldDamage = MaxshieldDamage;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle_Shield, this, &AShip::DeactivateShield, 7.0f);
			}
		}
	}
	
}

void AShip::ActivateShiledWithoutMana()
{
	float CoolDown = 15;

	if (!bCDShield)
	{
		if (ShieldIsOn == 0)
		{
			bCDShield = true;

			GetWorld()->GetTimerManager().SetTimer(CDHandle_Shield, this, &AShip::ShiledInCD, CoolDown);


			ShieldIsOn = 1;
			ShiledSound = UGameplayStatics::PlaySoundAttached(AbilitySound[1], this->ShipMeshComponent);

			ShiledSound->Play();
			//PlaySoundOnActor(AbilitySound[1], 1.f, 1.f);// HOW DO I STOP THIS?
			shieldDamage = MaxshieldDamage;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Shield, this, &AShip::DeactivateShield, 7.0f);
		}
	}

}


void AShip::DeactivateShield()
{	

	if (ShieldIsOn == 1)
	{	
		ShiledSound->Stop();
		UGameplayStatics::PlaySoundAttached(AbilitySound[0], this->ShipMeshComponent);
		ShieldIsOn = 0;
	}
}


void AShip::Blink()
{	
	float ManaCost = 20;
	float CoolDown = 4;

	if (Mana - ManaCost >= 0 && !bCDBlink)
	{
		Mana -= ManaCost;
		bCDBlink = true;

		GetWorld()->GetTimerManager().SetTimer(CDHandle_Blink, this, &AShip::BlinkInCD, CoolDown);
		//Play blink FX and SE
		if (AbilitySound.Num() > 2 && AbilityFX.Num() > 0)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[0], GetActorLocation());
			UGameplayStatics::PlaySoundAttached(AbilitySound[2], this->ShipMeshComponent);
		}	

		FRotator curFacing = GetActorRotation();
		FVector curLoc = GetActorLocation();

		//get facing 
		FVector destLoc = curLoc + curFacing.Vector() * 700;
		TeleportTo(destLoc, curFacing);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[0], GetActorLocation());
	}
}


void AShip::Rewind()
{	
	float ManaCost = 10;
	float CoolDown = 15;

	if (Mana - ManaCost >= 0 && !bCDRewind)
	{
		if (!bRewindInProcess)
		{	
			bRewindInProcess = true;

			bCDRewind = true;
			Mana -= ManaCost;
			curMana = Mana;


			//place a dim ship mesh to the triggered location as a visual placeholder.


			//record all ship's stats. should include cooldowns if implemented.
			curHealthR = health;
			curLocR = GetActorLocation();
			deathCountR = (int)DeathCount;

			//rewind back, restore 75% of health lost/added, restore cool downs
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Rewind, this, &AShip::RewindHelper, 7.f);

			//play fx and se
			if (AbilitySound.Num() > 3 && AbilityFX.Num() > 1)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[1], GetActorLocation());
				UGameplayStatics::PlaySoundAttached(AbilitySound[3], this->ShipMeshComponent);
			}

			bCDRewind = false;
			GetWorld()->GetTimerManager().SetTimer(CDHandle_Rewind, this, &AShip::RewindInCD, 5.f);
		}
	}
}

void AShip::RewindHelper()
{	
	//if not dead. teleport ship back to set location and restore 75 changes of the health 
	if (deathCountR == (int)DeathCount)
	{	
		bRewindInProcess = false;

		//play fx & se
		if (AbilitySound.Num() > 4 && AbilityFX.Num() > 1)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[1], GetActorLocation());
			UGameplayStatics::PlaySoundAttached(AbilitySound[4], this->ShipMeshComponent);
		}

		//restore coolldowns and mana if implemented.

		//could be either gain or lose health
		if (health + (curHealthR - health)*.75 <= 100)
		health += (curHealthR - health)*.75;
		else health = 100;
		
		if (Mana + (curMana - Mana)*.75 <= 100)
		Mana += (curMana - Mana)*.75;
		else Mana = 100;

		SetActorLocation(curLocR);

		InitCoolDowns();// renew all the CDs
		GetWorld()->GetTimerManager().SetTimer(CDHandle_Rewind, this, &AShip::RewindInCD, 10.f);


		if (AbilityFX.Num() > 1) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[1], GetActorLocation());
	}
	else{
		//print Valor margulis
	}
}


void AShip::TripleBlink()
{
	float ManaCost = 5;
	// there will be no cd limit for tripleBlink now.

	//float CoolDown = 1.5; //within 1.5 seconds, player can blink for 3 times. then a 2 sec CD.

	if (Mana - ManaCost >= 0 && !bCDTripleBlink)
	{
			Mana -= ManaCost;

	//Play blink FX and SE
		if (AbilitySound.Num() > 2 && AbilityFX.Num() > 0)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[0], GetActorLocation());
			UGameplayStatics::PlaySoundAttached(AbilitySound[2], this->ShipMeshComponent);
		}

		FRotator curFacing = GetActorRotation();
		FVector curLoc = GetActorLocation();

		//get facing 
		FVector destLoc = curLoc + curFacing.Vector() * 300;
		TeleportTo(destLoc, curFacing);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[0], GetActorLocation());
	}
}


//helper functions for cooldowns and lasting ability
void AShip::ShiledInCD(){ bCDShield = !bCDShield; }
void AShip::BlinkInCD(){ bCDBlink = !bCDBlink; }
void AShip::RewindInCD(){ bCDRewind = !bCDRewind; }
void AShip::TripleBlinkInCD(){bCDTripleBlink = !bCDTripleBlink; }
void AShip::HomingInCD(){ bHomingInProcess = false; bCDHoming = !bCDHoming; }
void AShip::BerserkInCD(){ bBerserkerInProgress = false; bCDBerserk = !bCDBerserk; }


void AShip::TripleBlinkInCDHelper()
{
	if (bCDTripleBlink == false)
	bCDTripleBlink = true;


	GetWorld()->GetTimerManager().SetTimer(CDHandle_TriBlink_2, this, &AShip::TripleBlinkInCD, 2);
}

void AShip::homingMissle()
{
	//invoke homing missle mesh in level 
	float ManaCost = 5;
	float CoolDown = .5f;
	
	if (Mana - ManaCost >= 0 && !bCDHoming)
	{
		if (!bHomingInProcess)
		{
			Mana -= ManaCost;
			bCDHoming = true;
			bHomingInProcess = true;	
			//UGameplayStatics::PlaySoundAttached(AbilitySound[1], this->ShipMeshComponent);
			GetWorld()->GetTimerManager().SetTimer(CDHandle_Homing, this, &AShip::HomingInCD, CoolDown);
		}
	}

}

void AShip::Berserk()
{
	//speed increases 1.5 time
	//take and deal 1.5 time damage
	float ManaCost = 20;
	float CoolDown = 15;


	if (Mana - ManaCost >= 0 && !bCDBerserk)
	{
		if (!bBerserkerInProgress)
		{
			Mana -= ManaCost;
			bCDBerserk = true;
			bBerserkerInProgress = true;

			CurMaxSpeed = MaxSpeed;
			CurShipSpeed = MoveSpeed;

			MaxSpeed *= 1.5;
			MoveSpeed *= 1.5;
			// deal/take damage part is done in TakeDamage function

			GetWorld()->GetTimerManager().SetTimer(CDHandle_BerserkInPro, this, &AShip::BerskerModeEnd, 10);
			GetWorld()->GetTimerManager().SetTimer(CDHandle_Berserk, this, &AShip::BerserkInCD, CoolDown);
			//sound & fx
			UGameplayStatics::SpawnEmitterAttached(AbilityFX[2],this->ShipMeshComponent);
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AbilityFX[2], GetActorLocation());
			UGameplayStatics::PlaySoundAttached(AbilitySound[5], this->ShipMeshComponent);
		}
	}
}

void AShip::BerskerModeEnd()
{
	bBerserkerInProgress = false;

	MaxSpeed = CurMaxSpeed;
	MoveSpeed = CurShipSpeed;

	//play sound effect 
}

// cooldowns will be re initialte after death
void AShip::InitCoolDowns() 
{
	bCDShield = false;
	bCDBlink = false;
	bCDRewind = false;
	bCDHoming = false;
	bCDTripleBlink = false;
	bCDBerserk = false;
}
	
float AShip::getMana(){ return Mana; }
void AShip::setMana(float m){ Mana = m; }

bool AShip::getbCDBlink(){ return bCDBlink; }

void AShip::initAbilityList(){

	for (int i = 0; i < AbilityClassList.Num(); i++)
	{	
		AAbility* curAbility = GetWorld()->SpawnActor<AAbility>(AbilityClassList[i], FVector::ZeroVector, FRotator::ZeroRotator);
		curAbility->owner = this;
		curAbility->AttachRootComponentToActor(this);
		Ability	List.Add(curAbility);
	}
}

void AShip::InvokeAbility(int numAbility)
{
	if (AbilityList.Num() > numAbility)
	{
		AbilityList[numAbility]->StartAbility();
	}
}


