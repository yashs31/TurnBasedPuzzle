// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_IsPlayerMoving.h"
#include <TurnBasedPuzzle/Characters/HeroCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <TurnBasedPuzzle/AI/EnemyAIController.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTS_IsPlayerMoving::UBTS_IsPlayerMoving()
{
	NodeName = TEXT("Is Player Moving");
}

void UBTS_IsPlayerMoving::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (const AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxCanMove.SelectedKeyName, HeroCharacter->GetVelocity().Length() > 0);
		}
	}
}
