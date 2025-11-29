// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "TurnBasedPuzzle/LevelActors/NodeBase.h"
#include "TurnBasedPuzzle/LevelActors/ThrowableActor.h"
#include <EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include "HeroController.h"
// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitMappingContext();
	
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

}

void AHeroCharacter::ReportNoise()
{
}

void AHeroCharacter::PlayerKilled()
{
}

void AHeroCharacter::PistolFire()
{
}

void AHeroCharacter::ThrowStone()
{
}

void AHeroCharacter::Teleport()
{
}

void AHeroCharacter::ClickNode()
{
}

void AHeroCharacter::MovePlayerToNodeLocation()
{
}

void AHeroCharacter::InitMappingContext()
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
	return false;
}

