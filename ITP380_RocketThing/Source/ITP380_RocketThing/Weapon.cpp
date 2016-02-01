// Fill out your copyright notice in the Description page of Project Settings.

#include "ITP380_RocketThing.h"
#include "Ship.h"
#include "Firable.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanFire = true;
	bIsFiring = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;
	firePoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Point"));
	firePoint->AttachTo(WeaponMesh);
}

void AWeapon::Initialize(AShip* owner){
	this->Owner = owner;
	OwnerShipNumber = Owner->PlayerNumber;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	intervalBetweenFire = 1 / FireRate;

}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeapon::setOwnerNum(int i){
	OwnerShipNumber = (int32)i;
}

void AWeapon::Fire(){
	if (bCanFire){
		if (FireSound)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		bIsFiring = true;
		FireFunction();
		bCanFire = false;
		UWorld* world = GetWorld();
		if (world){
			world->GetTimerManager().SetTimer(TimerHandle_ShotIntervalExpired, this, &AWeapon::Reload, intervalBetweenFire);
		}
	}
}

void AWeapon::FireFunction(){
	
	if (firedObject){
		UWorld* world = GetWorld();
		if (world){
			FActorSpawnParameters parameters = FActorSpawnParameters(); 
			parameters.bNoCollisionFail = true;
			parameters.Instigator = Owner;
			parameters.Name = GetProjectileName();
			FVector spawnLocation = GetActorLocation();
			FRotator spawnRotation = GetActorRotation();
			AActor* Spawned = world->SpawnActor(*firedObject, &spawnLocation, &spawnRotation,parameters);
			AFirable* firable = Cast<AFirable>(Spawned);
			firable->SetColor(ProjectileColor);
			firable->Instigator = Owner->GetController();
			firable->Damage = damage;
			firable->OwnerID = OwnerShipNumber;
		}
	}
}

/*
void AWeapon::setAllColor(AFirable* firable){
	static ConstructorHelpers::FObjectFinder< UMaterialInstance> Material_1(TEXT("MaterialInstanceConstant'/Game/Assets/Materials/EmissiveColorList/emissiveGreen_Inst.emissiveGreen_Inst'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material_2(TEXT("Material'/Game/Assets/Materials/EmissiveColorList/emissiveRed.emissiveRed'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material_3(TEXT("Material'/Game/Assets/Materials/EmissiveColorList/emissiveGreen.emissiveGreen'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material_4(TEXT("Material'/Game/Assets/Materials/EmissiveColorList/emissivePrupl.emissivePrupl'"));

	switch (OwnerShipNumber)
		case 1:{
		firable->FirableMesh->SetMaterial(0, Material_1);
	}

}*/

void AWeapon::StopFire(){
	bIsFiring = false;
}


FName AWeapon::GetProjectileName(){
	return "BaseProjectile";
}

void AWeapon::Reload(){
	bCanFire = true;
}

void AWeapon::SetProjectileColor(FLinearColor color){
	ProjectileColor = color;
}
