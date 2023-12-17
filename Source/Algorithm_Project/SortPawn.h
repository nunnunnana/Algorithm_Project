// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "SortActor.h"
#include "W_Sort.h"
#include "SortPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API ASortPawn : public ABasicPawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ASortPawn();

	UPROPERTY(EditAnyWhere)
	ASortActor* sortActor;

	TSubclassOf<UUserWidget> sortWidgetClass;
	UW_Sort* sortWidget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UMaterialInstance* currentMat;

	void Z();
	void X();
	void C();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

