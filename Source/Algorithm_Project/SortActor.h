// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortActorMesh.h"
#include "../../Plugins/UE5Coro/Source/UE5Coro/Public/UE5Coro.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Components/TimeLineComponent.h"
#include "SortActor.generated.h"

using namespace UE5Coro;

UCLASS()
class ALGORITHM_PROJECT_API ASortActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortActor();

	UPROPERTY(EditAnyWhere)
	int size;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int index;
	int currentIndex;
	int tmp;
	int bstart;
	int start;
	int end;
	bool IsSorting;

	UPROPERTY()
	ASortActorMesh* currentTarget;

	UPROPERTY()
	ASortActorMesh* arget;

	UPROPERTY()
	UMaterialInstance* whiteMat;

	UPROPERTY()
	UMaterialInstance* yellowtMat;

	UPROPERTY()
	UMaterialInstance* redMat;

	UPROPERTY()
	UMaterialInstance* blueMat;

	UPROPERTY()
	TArray<ASortActorMesh*> arrTarget;

	FTimerHandle Timer;
	UFUNCTION()
	void SetSelectionSortColor();

	UFUNCTION()
	void SetInjectionSortColor();

	UFUNCTION()
	void SetBubbleSortColor();

	UFUNCTION()
	void SetMergeSortColor(TArray<ASortActorMesh*>& v, int s, int e, int m);

	UFUNCTION()
	void SetQuickSortColor(TArray<ASortActorMesh*>& arr, int s, int e, int bs, int be);

	UFUNCTION()
	void QuickTest();

	UFUNCTION()
	void QuickTest_1();

	UFUNCTION()
	void Merge_Test(TArray<ASortActorMesh*>& v, int s);

	UFUNCTION()
	void SpawnActor(AActor* targetActor, int actorIndex);

	UFUNCTION()
	void SetArrayLocation();

	UFUNCTION()
	void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ShuffleArray();

	UFUNCTION()
	void SetArrTargetColor(UMaterialInstance* material, int targetIndex);

	UFUNCTION()
	void SelectionSort();

	UFUNCTION()
	void StartSelectionSort();

	UFUNCTION()
	void InjectionSort();

	UFUNCTION()
	void StartInjectionSort();

	UFUNCTION()
	void BubbleSort();

	UFUNCTION()
	void StartBubbleSort(); 

	UFUNCTION()
	void MergeSort();

	UFUNCTION()
	void StartMergeSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex);

	UFUNCTION()
	void QuickSort();

	UFUNCTION()
	void StartQuickSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex);

};
