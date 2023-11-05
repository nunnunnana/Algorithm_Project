// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "StackQueue.generated.h"

// Pawn C++ 기능 추가되면 사용
// DECLARE_DELEGATE(FDele_Single);

// 블루 프린트에서 사용하기 위해 다이나믹 사용
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_OnFulled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_OnEmptied);

UCLASS()
class ALGORITHM_PROJECT_API AStackQueue : public AActor
{
	GENERATED_BODY()
	
public:	
	//FDele_Single Fuc_DeleSingle;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FDele_OnFulled OnFulled;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FDele_OnEmptied OnEmptied;

	// Sets default values for this actor's properties
	AStackQueue();

	UPROPERTY()
		int top;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int size;

	UPROPERTY()
		AStaticMeshActor* currentTarget;

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


protected:
	UFUNCTION(BlueprintCallable)
		bool IsFull();

	UFUNCTION(BlueprintCallable)
		bool IsEmpty();

	UFUNCTION(BlueprintCallable)
		void Push();

	UFUNCTION(BlueprintCallable)
		void Pop();

	UFUNCTION(BlueprintCallable)
		void SpawnActor(AActor* targetActor, int height);

	UFUNCTION(BlueprintCallable)
		void RemoveActor();

};
