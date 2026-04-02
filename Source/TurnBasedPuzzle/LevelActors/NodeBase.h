// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeBase.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API ANodeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	ANodeBase* TeleportNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bIsTeleportNode=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bIsEndNode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bShowPanel1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bShowPanel2 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bShowPanel3 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	bool bShowPanel4 = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* DecoFinishMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* NodeCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* Panel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* Panel2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* Panel3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	UStaticMeshComponent* Panel4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NodeBase")
	class UNiagaraComponent* FX_Teleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeBase")
	TSubclassOf<UUserWidget> VictoryWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
