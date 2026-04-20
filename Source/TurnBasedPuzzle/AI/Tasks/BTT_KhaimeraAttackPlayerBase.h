// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTT_EnemyAttackPlayerBase.h"
#include "BTT_KhaimeraAttackPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDPUZZLE_API UBTT_KhaimeraAttackPlayerBase : public UBTT_EnemyAttackPlayerBase
{
	GENERATED_BODY()

public:
	UBTT_KhaimeraAttackPlayerBase();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
