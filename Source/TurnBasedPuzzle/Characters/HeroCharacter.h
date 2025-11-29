// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "HeroCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerMoved);


UCLASS()
class TURNBASEDPUZZLE_API AHeroCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SpawnStone();

	UFUNCTION(BlueprintCallable)
	void ReportNoise();

	UFUNCTION(BlueprintCallable)
	void PlayerKilled();

	UFUNCTION(BlueprintCallable)
	void PistolFire();

	UFUNCTION(BlueprintCallable)
	void ThrowStone();

	UFUNCTION(BlueprintCallable)
	void Teleport();

	UFUNCTION(BlueprintCallable)
	void ClickNode();

	UFUNCTION(BlueprintCallable)
	void MovePlayerToNodeLocation();

	UFUNCTION(BlueprintCallable)
	void InitMappingContext();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CanPlayerShoot() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputAction* IAMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputAction* IAFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputAction* IATeleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Input")
	class UInputAction* IAThrowStone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	bool bCanClickNode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	bool bCanThrowStone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	bool bCanTeleport = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	FVector NodeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	FVector StoneLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	float AcceptDistance = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	float MoveSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Ability")
	int32 PistolAmmo = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Dynamic References")
	class ANodeBase* TargetNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Dynamic References")
	class AThrowableActor* StoneInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Montage")
	UAnimMontage* Montage_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Montage")
	UAnimMontage* Montage_Entry;

	UPROPERTY()
	FTimerHandle TH_ResetPlayerMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> ShootObjectsQuery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneObjectsQuery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> ClickObjectsQuery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|SFX")
	USoundBase* Cue_Teleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|SFX")
	USoundBase* Cue_PistolShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|VFX")
	UParticleSystem* FX_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|VFX")
	UParticleSystem* FX_Teleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Projectile")
	TSubclassOf<AThrowableActor> ThrowableClass;


	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnPlayerDeath OnPlayerDeath;

	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnPlayerMoved OnPlayerMove;

	

};
