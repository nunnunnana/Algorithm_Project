// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActorMesh.h"

// Sets default values
ASortActorMesh::ASortActorMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 일회성 초기화 저장을 위한 구조체
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> findMesh;
		FConstructorStatics()
			: findMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	cubeMesh = ConstructorStatics.findMesh.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_Red.M_Base_Red'"));
	currentMat = findMat.Object;

}
// Called when the game starts or when spawned
void ASortActorMesh::BeginPlay()
{
	Super::BeginPlay();
	// index 값 만큼 메시 Spawn
	for (int i = 0; i <= index; i++) {
		SpawnMesh(i);
	}
	//SetActorColor(currentMat);
}

// StaticmeshComponent의 mesh, mobility 설정 함수
void ASortActorMesh::SpawnMesh(int height)
{
	// height 값 만큼 높이 설정
	height *= 100;
	FTransform MakeTransform(FRotator(0,0,0), FVector(0, 0, height));
	UStaticMeshComponent* mesh = (UStaticMeshComponent*)this->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, MakeTransform, false);
	mesh->SetMobility(EComponentMobility::Movable);
	mesh->SetStaticMesh(cubeMesh);
}

// 컴포넌트 색상 설정 함수
void ASortActorMesh::SetActorColor(UMaterialInstance* material)
{
	// StaticMeshComponent 가져오기
	TArray<UStaticMeshComponent*> Comps;
	GetComponents(Comps);
	if (Comps.Num() > 0)
	{
		// Component 수 만큼 Material 변경
		for (int i = 0; i < Comps.Num(); i++) {
			Comps[i]->SetMaterial(0, material);
		}
	}
}

// Called every frame
void ASortActorMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

