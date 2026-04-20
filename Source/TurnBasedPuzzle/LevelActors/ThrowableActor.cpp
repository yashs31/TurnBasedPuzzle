// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NodeBase.h"
#include <TurnBasedPuzzle/Characters/HeroCharacter.h>
#include <Kismet/GameplayStatics.h>
// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 500.f;
	ProjectileMovementComponent->MaxSpeed = 500.f;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 1000.f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AThrowableActor::OnSphereColliderBeginOverlap);
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableActor::ThrowActor(AActor* Actor, FVector InVelocity)
{
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->Velocity = InVelocity;
	ProjectileMovementComponent->HomingTargetComponent = Actor->GetRootComponent();
	ProjectileMovementComponent->HomingAccelerationMagnitude = 2000.f;
}

void AThrowableActor::OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ANodeBase* NodeBase = Cast<ANodeBase>(OtherActor))
	{
		if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(GetOwner()))
		{
			HeroCharacter->bCanClickNode = true;
			HeroCharacter->ReportNoise();
			if (Cue_Impact)
			{
				UGameplayStatics::PlaySound2D(this, Cue_Impact);
			}
			Destroy();
		}
	}
}

