// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GruxAttackPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <TurnBasedPuzzle/Characters/HeroCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>
#include <TurnBasedPuzzle/AI/EnemyAIController.h>

UBTT_GruxAttackPlayer::UBTT_GruxAttackPlayer()
{
	NodeName = TEXT("Grux Attack Player");
}

EBTNodeResult::Type UBTT_GruxAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (HeroCharacter->bIsAlive)
		{
			if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
			{
				if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
				{
					EnemyCharacter->AttackPlayer();
					EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxCanSeePlayer.SelectedKeyName, false);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		
	}
	return EBTNodeResult::Failed;
}
