// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Search_Points.h"
#include "UE5Coro.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Search.generated.h"

DECLARE_DELEGATE(FDele_OnDestinationReached);
DECLARE_DELEGATE(FDele_OnDestinationUnreached);

UCLASS()
class ALGORITHM_PROJECT_API ASearch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASearch();

	FDele_OnDestinationReached OnDestinationReached;
	FDele_OnDestinationUnreached OnDestinationUnreached;

	TArray<int32> IntArray;

	UPROPERTY(EditAnyWhere)
	int height = 0;

	UPROPERTY(EditAnyWhere)
	int width = 0;

	UPROPERTY(EditAnyWhere)
	int distribution = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle bfsTimer;

private:


	UPROPERTY()
	TArray<ASearch_Points*> arrPoints;

	UPROPERTY()
	TArray<ASearch_Points*> arrCurrentCell;

	UPROPERTY()
	TArray<ASearch_Points*> arrNeighborCell;

	UPROPERTY()
	TArray<ASearch_Points*> arrTotalCell;

	UPROPERTY()
	ASearch_Points* startPoint;

	UPROPERTY()
	ASearch_Points* endPoint;

	UPROPERTY()
	ASearch_Points* currentCell;

	UPROPERTY()
	ASearch_Points* nextCell;

	UPROPERTY()
	UMaterialInstance* greenMat;

	bool isfindEndPoint = false;

	int dijkstraCost = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DrawMap();

	UFUNCTION()
	void ResetMap();

	UFUNCTION()
	void StartBFS();

	UFUNCTION()
	void BFS();

	UFUNCTION()
	FAsyncCoroutine StartDFS(ASearch_Points* point);

	UFUNCTION()
	void StartDijkstra();

	UFUNCTION()
	void StartAstar();

	UFUNCTION()
	FAsyncCoroutine Research();

	UFUNCTION()
	void SetAllCostVisibility();

	UFUNCTION()
	void FindNeighborCell();

	UFUNCTION()
	void FindNeighborCell_IngnoreVisited();

};
