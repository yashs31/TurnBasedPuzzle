// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableStone.h"

void AThrowableStone::BeginPlay()
{
}

void AThrowableStone::Tick(float DeltaTime)
{
}

void AThrowableStone::ThrowActor(AActor* Actor, FVector InVelocity)
{
	Super::ThrowActor(Actor, InVelocity);
}
