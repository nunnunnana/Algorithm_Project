// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Search.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API ASearch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASearch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ResetMap();

	UFUNCTION()
	void StartBFS();

	UFUNCTION()
	void StartDFS();

	UFUNCTION()
	void StartDijkstra();

	UFUNCTION()
	void StartAstar();

	UFUNCTION()
	void SetCostVisibility();

};
