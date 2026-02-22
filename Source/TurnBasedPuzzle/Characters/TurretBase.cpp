// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include <Kismet/KismetSystemLibrary.h>
#include "HeroCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ATurretBase::ATurretBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TH_TracePlayer, this, &ATurretBase::TracePlayer, 1.5f, true,0.2f);
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretBase::TracePlayer()
{
	const FVector StartTrace = TurretMesh->GetSocketLocation(TurretSocket);
	const FVector EndTrace = StartTrace + (TurretMesh->GetForwardVector() * Distance);
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	const bool bHit = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), StartTrace, EndTrace, FVector(8.0f), FRotator(0),
		TraceObjectQuery, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

	if (bHit)
	{
		if (HitResult.GetActor()->ActorHasTag("Player"))
		{
			AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(HitResult.GetActor());
			HeroCharacter->PlayerKilled();
			GetWorldTimerManager().PauseTimer(TH_TracePlayer);
			if (Cue_BlastLaser)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), Cue_BlastLaser);
			}
			if (Anim_Fire)
			{
				TurretMesh->PlayAnimation(Anim_Fire, false);
			}
		}
	}
}

