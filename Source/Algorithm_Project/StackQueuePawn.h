// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "StackQueuePawn.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API AStackQueuePawn : public ABasicPawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AStackQueuePawn();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		AStackQueue* stackqueueActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Z();
	void X();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};