// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "StackQueue.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API AStackQueue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStackQueue();

	UPROPERTY()
		int top;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int size;

	UPROPERTY()
		AStaticMeshActor* currentTarget;

	UPROPERTY()
		TArray<AStaticMeshActor*> arrTarget;

	TSubclassOf<UUserWidget> W_MyStackQueue;
	W_MyStackQueue* MainHUDWidget;

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
		void SpawnActor();

	UFUNCTION(BlueprintCallable)
		void RemoveActor();

};
