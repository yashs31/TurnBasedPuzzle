// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <TurnBasedPuzzle/AI/EnemyAIController.h>
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollider"));
	AttackCollider->SetupAttachment(GetMesh());
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->HearingThreshold = 1000.f;
	PawnSensingComponent->LOSHearingThreshold = 1200.f;
	PawnSensingComponent->SightRadius = 400.f;
	PawnSensingComponent->SetPeripheralVisionAngle(20.f);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackColliderBeginOverlap);
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeenPawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnHearingPawn);
	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (EnemyType == EEnemyType::EET_Revenant)
		{
			//bind to hero character movement and flip
			Hero->OnPlayerMove.AddDynamic(this, &AEnemyCharacter::Flip);
		}
	}
	
}

void AEnemyCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AttackCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::Flip()
{
	const float Yaw = GetActorRotation().Yaw;
	if (Yaw == 0.0f)
	{
		SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
	else if (Yaw == 180.0f)
	{
		SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else
	{
		SetActorRotation(FRotator(0.0f, Yaw * -1, 0.0f));
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::EnemyKilled()
{
	bIsAlive = false;
	SetLifeSpan(1.0f);
}

void AEnemyCharacter::AttackPlayer()
{
	if (UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if(Montage_Attack)
		{
			AnimInstance->Montage_Play(Montage_Attack);
			if (Cue_AttackSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(),Cue_AttackSound);
			}
		}
	}
}

void AEnemyCharacter::OnAttackColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(OtherActor))
	{
		Hero->PlayerKilled();
		if (Cue_AttackSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), Cue_AttackSound);
		}
	}
}

void AEnemyCharacter::OnSeenPawn(APawn* Pawn)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(Pawn))
	{
		HeroCharacter->bIsMoving = false;
		HeroCharacter->bCanClickNode = false;
		if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController()))
		{
			switch (EnemyType)
			{
			case EEnemyType::EET_Khaimera:
				EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_CanSeePlayer, true);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(BB_PlayerLocation, HeroCharacter->GetActorLocation());
				break;
			case EEnemyType::EET_Revenant:
				bCanShoot = true;
				HeroCharacter->PlayerKilled();
				break;
			case EEnemyType::EET_Grux:
				EnemyController ->GetBlackboardComponent()->SetValueAsBool(BB_CanSeePlayer, true);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(BB_PlayerLocation, HeroCharacter->GetActorLocation());
				EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxCanMove, true);
				EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxHeadNoise, false);
				break;
			default:
				break;

			}
		}
		
	}
}

void AEnemyCharacter::OnHearingPawn(APawn* Instigator, const FVector& Location, float Volume)
{
	if (EnemyType == EEnemyType::EET_Grux)
	{
		if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController()))
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxCanMove,true);
			EnemyController->GetBlackboardComponent()->SetValueAsVector(BB_NoiseLocation, Location);
		}
	}
}

