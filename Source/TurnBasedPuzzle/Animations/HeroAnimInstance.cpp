// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAnimInstance.h"
#include <TurnBasedPuzzle/Characters/HeroCharacter.h>

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	HeroCharacter = Cast<AHeroCharacter>(TryGetPawnOwner());
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (HeroCharacter)
	{
		bIsAlive = HeroCharacter->bIsAlive;
		//bIsMoving = HeroCharacter->bIsMoving;
		bIsMoving = HeroCharacter->GetVelocity().Length()>0 ? true : false;
	}
}

