// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "TurnBasedGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDPUZZLE_API ATurnBasedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATurnBasedGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TurnBasedGameModeBase")
	FName LevelToLoad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TurnBasedGameModeBase")
	TSubclassOf<UUserWidget> GameOverWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TurnBasedGameModeBase")
	UUserWidget* GameOverScreen;

	UPROPERTY()
	FTimerHandle TH_GameOverScreen;

	UFUNCTION(BlueprintCallable, Category = "TurnBasedGameModeBase")
	void SetNextLevel(FName NextLevel);

	UFUNCTION(BlueprintCallable, Category = "TurnBasedGameModeBase")
	void OpenNextLevel();

	UFUNCTION(BlueprintCallable, Category = "TurnBasedGameModeBase")
	void RestartLevel();

	UFUNCTION(BlueprintCallable, Category = "TurnBasedGameModeBase")
	void ShowGameOverScreen();
	
	UFUNCTION()
	void ActivateGameOverScreen();

protected:
	virtual void BeginPlay() override;
};
