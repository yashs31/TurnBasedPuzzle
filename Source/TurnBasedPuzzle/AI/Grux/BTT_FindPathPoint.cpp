// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindPathPoint.h"
#include <TurnBasedPuzzle/AI/EnemyAIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>
#include <Kismet/KismetMathLibrary.h>

UBTT_FindPathPoint::UBTT_FindPathPoint()
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTT_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			if (EnemyCharacter->PatrolPath != nullptr)
			{
				const int32 PatrolIndex = EnemyController->GetBlackboardComponent()->GetValueAsInt(BB_PatrolIndex.SelectedKeyName);
				const FVector PathLocation = UKismetMathLibrary::TransformLocation(EnemyCharacter->PatrolPath->GetActorTransform(), 
					EnemyCharacter->PatrolPath->PathPoitns[PatrolIndex]);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(BB_PathLocation.SelectedKeyName, PathLocation);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
