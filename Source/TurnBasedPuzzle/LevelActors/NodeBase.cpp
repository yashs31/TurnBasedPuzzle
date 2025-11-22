// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBase.h"

// Sets default values
ANodeBase::ANodeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANodeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

