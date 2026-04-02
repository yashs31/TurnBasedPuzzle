// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "../LevelActors/PatrolPath.h"
#include "EnemyCharacter.generated.h"

UENUM()
enum class EEnemyType : uint8
{
	EET_None UMETA(DisplayName = "None"),
	EET_Khaimera UMETA(DisplayName = "Khaimera"),
	EET_Revenant UMETA(DisplayName = "Revenant"),
	EET_Grux UMETA(DisplayName = "Grux")
};

UCLASS()
class TURNBASEDPUZZLE_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	class UBoxComponent* AttackCollider;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void EnemyKilled();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void AttackPlayer();

	///----Revenant----///
	UFUNCTION(BlueprintCallable, Category = "Enemy|Revenant")
	void Flip();

	UFUNCTION()
	void OnAttackColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSeenPawn(APawn* Pawn);

	UFUNCTION()
	void OnHearingPawn(APawn* InstigatorPawn, const FVector& Location, float Volume);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Montage")
	UAnimMontage* Montage_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|SFX")
	USoundBase* Cue_AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Socket")
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	EEnemyType EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Khaimera")
	FName BB_CanSeePlayer=TEXT("bCanSeePlayer");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Khaimera")
	FName BB_PlayerLocation = TEXT("PlayerLocation");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Grux")
	APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Grux")
	FName BB_GruxCanMove = TEXT("bGruxCanMove");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Grux")
	FName BB_GruxHeadNoise = TEXT("GruxHearNoise");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Grux")
	FName BB_NoiseLocation = TEXT("NoiseLocation");
};
