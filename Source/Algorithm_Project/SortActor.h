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

	UPROPERTY()
	ASortActorMesh* currentTarget;

	UPROPERTY()
	UMaterialInstance* currentMat;

	UPROPERTY()
	TArray<ASortActorMesh*> arrTarget;

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

};
