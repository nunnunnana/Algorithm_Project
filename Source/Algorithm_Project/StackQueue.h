// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StackQueue.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API AStackQueue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStackQueue();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<int32> Stack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int top;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool check;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
		void IsFull();

	UFUNCTION(BlueprintCallable)
		void IsEmpty();

	UFUNCTION(BlueprintCallable)
		void push();

	UFUNCTION(BlueprintCallable)
		void pop();

};
