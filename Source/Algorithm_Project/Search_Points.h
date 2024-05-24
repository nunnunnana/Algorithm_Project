// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "Search_Points.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API ASearch_Points : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASearch_Points();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticMesh;

	UPROPERTY()
	UStaticMesh* cubeMesh;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstance* currentMat;

	UPROPERTY(EditAnyWhere)
	bool isWall = false;

	UPROPERTY(EditAnyWhere)
	bool isEndpoint = false;

	UPROPERTY(EditAnyWhere)
	bool isVisited = false;

	UPROPERTY(EditAnyWhere)
	int cost = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	

	UFUNCTION()
	void SpawnActor(FVector location, FVector color);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
