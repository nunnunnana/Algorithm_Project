// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "BasicPawn.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API ABasicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPawn();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float moveSpeed = 400;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float mouseSpeed = 100;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);
	void Turn(float AxisValue);		
	void LookUp(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
