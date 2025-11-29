// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include <TurnBasedPuzzle/Characters/EnemyCharacter.h>

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (EnemyCharacter)
	{
		bIsAlive = EnemyCharacter->bIsAlive;
		//bIsMoving = HeroCharacter->bIsMoving;
		bIsMoving = EnemyCharacter->GetVelocity().Length() > 0 ? true : false;
		bCanShoot= EnemyCharacter->bCanShoot;
	}
}
