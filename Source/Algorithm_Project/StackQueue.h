// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "StackQueue.generated.h"

// Pawn C++ 기능 추가되면 사용
DECLARE_DELEGATE(FDele_OnFulled);
DECLARE_DELEGATE(FDele_OnEmptied);

UCLASS()
class ALGORITHM_PROJECT_API AStackQueue : public AActor
{
	GENERATED_BODY()
	
public:	
		FDele_OnFulled OnFulled;

		FDele_OnEmptied OnEmptied;

	// Sets default values for this actor's properties
	AStackQueue();

	UPROPERTY()
		int top;

	UPROPERTY(EditAnyWhere)
		int size;

	UPROPERTY()
		AStaticMeshActor* currentTarget;

	UPROPERTY()
		UStaticMeshComponent* staitcMesh;

	UPROPERTY()
		UStaticMesh* cubeMesh;

	UPROPERTY()
		TArray<AStaticMeshActor*> arrTarget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Push();

	UFUNCTION()
		void Pop();


protected:
	UFUNCTION()
		bool IsFull();

	UFUNCTION()
		bool IsEmpty();

	UFUNCTION()
		void SpawnActor(AActor* targetActor, int height);

	UFUNCTION()
		void RemoveActor();

};
