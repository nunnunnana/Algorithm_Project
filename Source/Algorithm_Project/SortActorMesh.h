// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortActorMesh.generated.h"

UCLASS()
class ALGORITHM_PROJECT_API ASortActorMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortActorMesh();

	UPROPERTY(EditAnyWhere)
	int index;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* staticMesh;

	UPROPERTY()
	UStaticMesh* cubeMesh;

	UPROPERTY()
	UMaterialInstance* currentMat;

	UFUNCTION()
	void SpawnMesh(int height);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetActorColor(UMaterialInstance* material);

};
