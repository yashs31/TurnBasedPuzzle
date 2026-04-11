// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyAttackPlayerBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>
#include <TurnBasedPuzzle/AI/EnemyAIController.h>

UBTT_EnemyAttackPlayerBase::UBTT_EnemyAttackPlayerBase()
{
	NodeName = TEXT("Enemy Attack Player Base");
}

EBTNodeResult::Type UBTT_EnemyAttackPlayerBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("BTT BaseClass is executed"));
	return EBTNodeResult::Failed;
}
