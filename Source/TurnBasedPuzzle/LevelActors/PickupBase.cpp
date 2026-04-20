// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"
#include <TurnBasedPuzzle/Characters/HeroCharacter.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	PickupMesh->SetCanEverAffectNavigation(false);
	BoxCollider->SetCanEverAffectNavigation(false); 
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnBoxColliderBeginOverlap);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		switch (PickupType)
		{
			case EPickupType::EPT_Stone:
				HeroCharacter->SpawnStone();
				HeroCharacter->ThrowStone();
				if (Cue_Pickup)
				{
					UGameplayStatics::PlaySound2D(this, Cue_Pickup);
				}
				Destroy();
			break;

			case EPickupType::EPT_Pistol:
				HeroCharacter->bCanShoot = true;
				HeroCharacter->PistolAmmo = AmmoCount;
				if (Cue_Pickup)
				{
					UGameplayStatics::PlaySound2D(this, Cue_Pickup);
				}
				Destroy();
				break;
		}
	}
}

