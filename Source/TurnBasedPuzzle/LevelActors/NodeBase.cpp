// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBase.h"
#include <Components/BoxComponent.h>
#include "NiagaraComponent.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include "Blueprint/UserWidget.h"
#include "TurnBasedPuzzle/Misc/TurnBasedGameModeBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ANodeBase::ANodeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);
	NodeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeCollider"));
	NodeCollider->SetupAttachment(RootComponent);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	DecoFinishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecoFinishMesh"));
	DecoFinishMesh->SetupAttachment(BaseMesh);
	Panel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel1Mesh"));
	Panel1->SetupAttachment(BaseMesh);
	Panel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel2Mesh"));
	Panel2->SetupAttachment(BaseMesh);
	Panel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel3Mesh"));
	Panel3->SetupAttachment(BaseMesh);
	Panel4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel4Mesh"));
	Panel4->SetupAttachment(BaseMesh);
	FX_Teleport = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FX_Teleport"));

	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NodeCollider->SetGenerateOverlapEvents(true);
	Panel1->SetVisibility(false);
	Panel2->SetVisibility(false);
	Panel3->SetVisibility(false);
	Panel4->SetVisibility(false);
	DecoFinishMesh->SetVisibility(false);
	NodeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void ANodeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANodeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Panel1->SetVisibility(bShowPanel1);
	Panel2->SetVisibility(bShowPanel2);
	//Panel3->SetVisibility(bShowPanel3);
	//Panel4->SetVisibility(bShowPanel4);
}

// Called every frame
void ANodeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ANodeBase::OnBoxColliderBeginOverlap);
}

void ANodeBase::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		HeroCharacter->bIsMoving = false;
		if (bIsEndNode)
		{
			CreateWidget<UUserWidget>(GetWorld(), VictoryWidget)->AddToViewport(0);
			if (ATurnBasedGameModeBase* GameMode = Cast<ATurnBasedGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				GameMode->SetNextLevel(LevelName);
			}
		}
	}
}

