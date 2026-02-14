// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include <EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include "HeroController.h"
#include <Kismet/GameplayStatics.h>
#include "TurnBasedPuzzle/LevelActors/NodeBase.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "TurnBasedPuzzle/LevelActors/ThrowableActor.h"
#include "TurnBasedPuzzle/LevelActors/ThrowableStone.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/KismetMathLibrary.h>
// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnNoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComponent"));
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	InsertMappingContext();
	
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddOffsetToPlayer(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Pistol
		EIC->BindAction(IAFire, ETriggerEvent::Started, this, &AHeroCharacter::PistolFire);

		//Node Click
		EIC->BindAction(IAMove, ETriggerEvent::Started, this, &AHeroCharacter::ClickNode);

		//Throw Stone
		EIC->BindAction(IAThrowStone, ETriggerEvent::Started, this, &AHeroCharacter::ThrowStone);

		//Teleport
		EIC->BindAction(IATeleport, ETriggerEvent::Started, this, &AHeroCharacter::Teleport);
	}
}

void AHeroCharacter::SpawnStone()
{
	if (StoneClass)
	{
		const FVector SpawnLocation = GetActorLocation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.Owner = this;
		StoneInstance = GetWorld()->SpawnActor<AThrowableActor>(StoneClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		const FName SocketName = FName("StoneSocket");
		StoneInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, SocketName);
		StoneInstance->SetActorScale3D(FVector(0.7f));
	}
}

void AHeroCharacter::ReportNoise()
{
	if (PawnNoiseEmitterComponent)
	{
		if (TargetNode)
		{
			PawnNoiseEmitterComponent->MakeNoise(TargetNode,1000,StoneLocation);
		}
	}
}

void AHeroCharacter::PlayerKilled()
{
	bIsAlive = false;
	bCanClickNode = false;
	bCanShoot = false;
	if (Cue_DeathSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(),Cue_DeathSound);
	}
	if (OnPlayerDeath.IsBound())
	{
		OnPlayerDeath.Broadcast();
	}
}

void AHeroCharacter::PistolFire()
{
}

void AHeroCharacter::ThrowStone()
{
	if (bCanThrowStone)
	{
		bCanThrowStone = false;
		bCanClickNode = false;

		if (const AHeroController* HeroController = Cast<AHeroController>(GetController()))
		{
			FHitResult HitResult;
			if (HeroController->GetHitResultUnderCursorForObjects(StoneObjectsQuery, true, HitResult))
			{
				if (ANodeBase* NodeBase = Cast<ANodeBase>(HitResult.GetActor()))
				{
					TargetNode = NodeBase;
					StoneLocation = HitResult.Location;
					const FRotator YawRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), StoneLocation);
					if (TargetNode)
					{
						if (!TargetNode->BoxCollider->IsOverlappingActor(this))
						{
							if (StoneInstance)
							{
								StoneInstance->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
								const FVector VecDistance = NodeLocation - GetActorLocation();
								const FVector Velocity = UKismetMathLibrary::MakeVector(VecDistance.X, VecDistance.Y , VecDistance.Z*600.f);

								Cast<AThrowableStone>(StoneInstance)->ThrowStone(this, Velocity);
							}
						}

					}
				}
			}
		}
	}
}

void AHeroCharacter::Teleport()
{
	if (bCanTeleport)
	{
		TArray<AActor*> OverlappedActors;
		GetCapsuleComponent()->GetOverlappingActors(OverlappedActors, ANodeBase::StaticClass());
		if (const ANodeBase* NodeBase = Cast<ANodeBase>(OverlappedActors[0]))
		{
			if (NodeBase->TeleportNode != nullptr)
			{
				if (Cue_Teleport)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), Cue_Teleport);
					if (FX_Teleport)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Teleport, NodeBase->TeleportNode->GetActorLocation());
						SetActorLocation(NodeBase->TeleportNode->GetActorLocation());
						//no code of rotation as of yet
					}
				}
			}
		}
	}
}

void AHeroCharacter::ClickNode()
{
}

void AHeroCharacter::MovePlayerToNodeLocation()
{
}

void AHeroCharacter::InsertMappingContext()
{
	if (AHeroController* HeroController = Cast<AHeroController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(HeroController->GetLocalPlayer()))
		{
			if (HeroMappingContext)
			{
				EnhancedInputLocalPlayerSubsystem->AddMappingContext(HeroMappingContext,0);
			}
		}
	}
}

bool AHeroCharacter::CanPlayerShoot() const
{
	return PistolAmmo>0 && bIsAlive&& bCanShoot;
}

void AHeroCharacter::ResetPlayerMovement()
{
	bCanClickNode = true;
}

void AHeroCharacter::AddOffsetToPlayer(float DeltaTime)
{
	if (bIsMoving)
	{
		const FVector OffsetLocation = FMath::VInterpTo(GetActorLocation(), NodeLocation, DeltaTime, MoveSpeed);
		SetActorLocation(OffsetLocation);

	}
}

