// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameModeBase.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include <Kismet/GameplayStatics.h>

ATurnBasedGameModeBase::ATurnBasedGameModeBase()
{
}

void ATurnBasedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameOverScreen = CreateWidget<UUserWidget>(GetWorld(), GameOverWidget);
	GameOverScreen->AddToViewport();
	GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		HeroCharacter->OnPlayerDeath.AddDynamic(this, &ATurnBasedGameModeBase::ShowGameOverScreen);
	}
}

void ATurnBasedGameModeBase::SetNextLevel(FName NextLevel)
{
	LevelToLoad = NextLevel;
}

void ATurnBasedGameModeBase::OpenNextLevel()
{
	if (!LevelToLoad.IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad,true);
	}
}

void ATurnBasedGameModeBase::RestartLevel()
{
	const FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevel, true);
}

void ATurnBasedGameModeBase::ShowGameOverScreen()
{
	if (GameOverScreen)
	{
		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATurnBasedGameModeBase::ActivateGameOverScreen()
{
	if (!GetWorldTimerManager().IsTimerActive(TH_GameOverScreen))
	{
		GetWorldTimerManager().SetTimer(TH_GameOverScreen, this, &ATurnBasedGameModeBase::ShowGameOverScreen, 1.0f, false,2.f);
	}
}
