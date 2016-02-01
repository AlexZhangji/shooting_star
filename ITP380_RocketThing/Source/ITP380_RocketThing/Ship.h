// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ITP380_RocketThingPawn.h"
#include "Weapon.h"
#include "Ship.generated.h"

class ASpawningVolume;
class AAbility;

UENUM(BlueprintType)
enum class AbilityType : uint8{
	Blink UMETA(DisplayName = "Blink"),
	Missile UMETA(DisplayName = "Missile"),
	Shield	UMETA(DisplayName = "Shield"),
	ShortBlink UMETA(DisplayName = "SBlink"),
	Rewind UMETA(DisplayName = "Rewind"),
	Beserk UMETA(DisplayName = "Beserk"),
	Homing UMETA(Displayname = "Homing")
};


UCLASS()
class ITP380_ROCKETTHING_API AShip : public APawn
{
	GENERATED_BODY()
	
protected:
	//float health;  decleared as UPROPERTY
	float armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AbilityType firstAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AbilityType secondAbility;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
		UTexture2D* firstAbilityImage;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
		UTexture2D* secondAbilityImage;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
		UTexture2D* firstAbilityImageCooldown;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
		UTexture2D* secondAbilityImageCooldown;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<TSubclassOf<AWeapon>> AllWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon) // 
	TArray<AWeapon*> Weapons;

	AAbility* Ability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon) // add for blueprint access for damage
	AWeapon* SelectedWeapon;

	int WeaponIndex;

	//Engine engine;

	float forceFeedbackDamage;

private:
	float startingZPosition;
	bool bIsDead;

	//add for death count
	bool alreadyDead;


	void ProcessDeath();

public:
	float XFacing;
	float YFacing;

	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool firstAbilityOnCooldown();

	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool secondAbilityOnCooldown();

	FLatentActionInfo f;
	//component variables
	UPROPERTY(Category = Appearance, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(Category = Appearance, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* LeftEngine;

	UPROPERTY(Category = Appearance, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* RightEngine;

	UPROPERTY(Category = Appearance, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UPointLightComponent* PointLight;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//death aniamtion
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathAnim;

	//set up player stats for blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float MaxMana;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 DeathCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 PlayerNumber;// level blueprint will set this value when create player

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 DefaultWeaponNum;// level blueprint will set this value when create player

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 TotalPlayerNum;// level blueprint will set this value when create player

	//check if the shield is activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int32 ShieldIsOn;
	
	// Sets default values for this pawn's properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		float damping = 1;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
		float MaxSpeed = 5000;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
		float handling = .5;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 5;

	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadWrite)
		ASpawningVolume* SpawningVolume;

	AShip(const FObjectInitializer& ObjectInitializer);

	virtual void Move(FVector input, float DeltaTime);

	virtual void Rotate(FVector MoveDirection, float DeltaSeconds);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PawnStartFire(uint8 FireModeNum) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void StartAbility();

	virtual void EndAbility();

	void SwitchWeapon(int increment);

    float TakeDamage(float Damage, struct FDamageEvent const& DamageEven, AController* EventInstigator, AActor* DamageCauser) override;

	// Hit effects migrated from SHMUP. The plan is to play when dead
	UPROPERTY(EditDefaultsOnly, Category = Effects)
		UParticleSystem* HitFX;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		TArray<UParticleSystem*> AbilityFX;

	void RespawnShip(); // test for respawn

	FTimerHandle TimerHandle_Respawn;
	FTimerHandle TimerHandle_Shield;
	FTimerHandle TimerHandle_Rewind;
	FTimerHandle CDHandle_Shield;
	FTimerHandle CDHandle_Blink;
	FTimerHandle CDHandle_Rewind;
	FTimerHandle CDHandle_TriBlink;
	FTimerHandle CDHandle_TriBlink_2;
	FTimerHandle CDHandle_Homing;
	FTimerHandle CDHandle_Homing2;
	FTimerHandle CDHandle_Berserk;
	FTimerHandle CDHandle_BerserkInPro;

	void PlayRequiem();



	// Called when the ship gets into range of a HealthPack
	void ConsumeHealthPack(float HealthBoost);

	//sound effect for ship abilities and Misc.
	UPROPERTY(Category = Sound, EditDefaultsOnly)
	TArray<USoundCue*> AbilitySound;

	UPROPERTY(Category = Sound, EditDefaultsOnly)	
		TArray<USoundCue*> mySound;

	UPROPERTY(Category = Sound, EditDefaultsOnly)
		TArray<USoundCue*> MiscSound;

	//amount of damage shield will endure
	float shieldDamage;
	float MaxshieldDamage;

	UAudioComponent* ShiledSound;

	void useFirstAbility();

	void useSecondAbility();

	//Ship Abilities
	void ActivateShiled();

	void ActivateShiledWithoutMana();

	void DeactivateShield();

	//void Blink();

	void Rewind();
	void RewindHelper();

	//helper var for rewind
	float curHealthR;
	FVector curLocR;
	int deathCountR;
	float curMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Score)
	int32 score = 0;

	//may add Mana and cooldown

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bRewindInProcess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bCanSpawnIlussion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bHomingInProcess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bBerserkerInProgress;

	void TripleBlink();
	void Blink();

	void homingMissle();
	void Berserk();

	//Cooldown helper Var
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDShield;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDBlink;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDRewind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDTripleBlink;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDHoming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCDBerserk;

	UFUNCTION(BlueprintCallable, Category = Player)
		void SetPlayerIDAndColor(int32 ID, FLinearColor col);

	void InitCoolDowns();
	void ShiledInCD();
	void RewindInCD();
	void BlinkInCD();
	void TripleBlinkInCD();
	void TripleBlinkInCDHelper();
	void HomingInCD();
	void BerserkInCD();

	bool getbCDBlink();
	float getMana();	
	void setMana(float m);

	float CurMaxSpeed;
	float CurShipSpeed;

	void BerskerModeEnd();

	void initAbilityList();

	void InvokeAbility(int numAbility);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TArray<TSubclassOf<AAbility>> AbilityClassList;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TArray<AAbility*> AbilityList;
};
	
