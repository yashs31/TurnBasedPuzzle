// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_KhaimeraAttackPlayerBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>
#include <TurnBasedPuzzle/AI/EnemyAIController.h>

UBTT_KhaimeraAttackPlayerBase::UBTT_KhaimeraAttackPlayerBase()
{
	NodeName = TEXT("Khaimera Attack Player Base");
}

EBTNodeResult::Type UBTT_KhaimeraAttackPlayerBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EnemyCharacter->AttackPlayer();
		if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_CanSeePlayer.SelectedKeyName, false);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
