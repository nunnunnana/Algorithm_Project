// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortActorMesh.h"
#include "Kismet/KismetArrayLibrary.h"
#include "SortActor.generated.h"

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

	bool IsSorting;

	UPROPERTY()
	ASortActorMesh* currentTarget;

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

	void SetSelectionSortColor();

	void SetInjectionSortColor();

	void SetBubbleSortColor();

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

};
