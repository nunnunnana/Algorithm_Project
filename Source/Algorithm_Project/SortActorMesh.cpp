// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActorMesh.h"

// Sets default values
ASortActorMesh::ASortActorMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ȸ�� �ʱ�ȭ ������ ���� ����ü
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
	// index �� ��ŭ �޽� Spawn
	for (int i = 0; i <= index; i++) {
		SpawnMesh(i);
	}
	//SetActorColor(currentMat);
}

// StaticmeshComponent�� mesh, mobility ���� �Լ�
void ASortActorMesh::SpawnMesh(int height)
{
	// height �� ��ŭ ���� ����
	height *= 100;
	FTransform MakeTransform(FRotator(0,0,0), FVector(0, 0, height));
	UStaticMeshComponent* mesh = (UStaticMeshComponent*)this->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, MakeTransform, false);
	mesh->SetMobility(EComponentMobility::Movable);
	mesh->SetStaticMesh(cubeMesh);
}

// ������Ʈ ���� ���� �Լ�
void ASortActorMesh::SetActorColor(UMaterialInstance* material)
{
	// StaticMeshComponent ��������
	TArray<UStaticMeshComponent*> Comps;
	GetComponents(Comps);
	if (Comps.Num() > 0)
	{
		// Component �� ��ŭ Material ����
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

