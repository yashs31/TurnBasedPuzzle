// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_IncrementIndex.h"
#include <TurnBasedPuzzle/AI/EnemyAIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>
#include <Kismet/KismetMathLibrary.h>
UBTT_IncrementIndex::UBTT_IncrementIndex()
{
	NodeName = TEXT("Increment Index");
}

EBTNodeResult::Type UBTT_IncrementIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			if (EnemyCharacter->PatrolPath != nullptr)
			{
				const int32 PatrolIndex = EnemyCharacter->PatrolPath->PathPoitns.Num() - 1;
				const int32 BlackboardIndex = EnemyController->GetBlackboardComponent()->GetValueAsInt(BB_PatrolIndex.SelectedKeyName);
				if (PatrolIndex == BlackboardIndex)
				{
					EnemyController->GetBlackboardComponent()->SetValueAsInt(BB_PatrolIndex.SelectedKeyName, 0);
					return EBTNodeResult::Succeeded;
				}
				EnemyController->GetBlackboardComponent()->SetValueAsInt(BB_PatrolIndex.SelectedKeyName, BlackboardIndex + 1);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
