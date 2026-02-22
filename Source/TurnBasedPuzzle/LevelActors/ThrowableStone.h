// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThrowableActor.h"
#include "ThrowableStone.generated.h"
/**
 * 
 */
UCLASS()
class TURNBASEDPUZZLE_API AThrowableStone : public AThrowableActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ThrowActor(AActor* Actor, FVector InVelocity) override;
};
