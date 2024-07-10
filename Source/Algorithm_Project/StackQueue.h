// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Components/TimeLineComponent.h"
#include "StackQueue.generated.h"

DECLARE_DELEGATE(FDele_OnFulled);
DECLARE_DELEGATE(FDele_OnEmptied);

class UCurveFloat;

UCLASS()
class ALGORITHM_PROJECT_API AStackQueue : public AActor
{
	GENERATED_BODY()
	
public:	
		FDele_OnFulled OnFulled;

		FDele_OnEmptied OnEmptied;

	// Sets default values for this actor's properties
	AStackQueue();

	UPROPERTY(EditAnyWhere)
		int size;

		int top = -1;

		int front = 0;

		int rear = 0;

	UPROPERTY()
		AStaticMeshActor* currentTarget;

	UPROPERTY()
		UStaticMeshComponent* staticMesh;

	UPROPERTY()
		UStaticMesh* cubeMesh;

	UPROPERTY()
		UMaterial* currentMat;
;
	UPROPERTY()
		TArray<AStaticMeshActor*> arrTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline StackTimeline;
	FTimeline EnqueueTimeline;
	FTimeline DequeueTimeline;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> StackTimelineDirection;

	UPROPERTY(EditAnyWhere, Category = "Timeline")
		UCurveFloat* curve = nullptr;
private:
	float currentZLocation;
	float targetZLocation;
	float currentYLocation;
	float targetYLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Push();

	UFUNCTION()
		void Pop();

	UFUNCTION()
		void Enqueue();

	UFUNCTION()
		void Dequeue();

	UFUNCTION()
		void ClearStack();

	UFUNCTION()
		void ClearQueue();

protected:
	UFUNCTION()
		bool IsStackFull();

	UFUNCTION()
		bool IsStackEmpty();

	UFUNCTION()
		bool IsQueueFull();

	UFUNCTION()
		bool IsQueueEmpty();

	UFUNCTION()
		void SpawnStackActor(AActor* targetActor, int height);

	UFUNCTION()
		void RemoveStackActor();

	UFUNCTION()
		void SpawnQueueActor(AActor* targetActor, int width);

	UFUNCTION()
		void RemoveQueueActor();

	UFUNCTION()
		void ClearActors(int num);

	UFUNCTION()
		void SpawnActor(FVector location, FVector color);

	UFUNCTION()
		void RemoveActor(int index);
	UFUNCTION()
		void StackUpdate(float Alpha);
	UFUNCTION()
		void StackFinished();
	UFUNCTION()
		void EnqueueUpdate(float Alpha);
	UFUNCTION()
		void DequeueUpdate(float Alpha);
	UFUNCTION()
		void DequeueFinished();
};
