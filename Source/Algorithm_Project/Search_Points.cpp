// Fill out your copyright notice in the Description page of Project Settings.


#include "Search_Points.h"

// Sets default values
ASearch_Points::ASearch_Points()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

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

	staticMesh->SetStaticMesh(cubeMesh);
	// Set as root component
	RootComponent = staticMesh;

	// ��Ƽ���� ����
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findMat(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_White.M_Base_White'"));
	currentMat = findMat.Object;
	staticMesh->SetMaterial(0, currentMat);

	// Set scale
	SetActorScale3D(FVector(0.5f));

}

// Called when the game starts or when spawned
void ASearch_Points::BeginPlay()
{
	Super::BeginPlay();
	//FVector currentLocation = this->GetActorLocation();
	//SpawnActor(currentLocation, FVector(0, 0, 0));

}

// Called every frame
void ASearch_Points::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ���� ����
void ASearch_Points::SpawnActor(FVector location, FVector color)
{
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), location, rotation, SpawnParams);
	// ������ ��ġ �̵��� ���� Movable�� ����
	target->SetMobility(EComponentMobility::Movable);
	target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh);
	target->GetStaticMeshComponent()->SetMaterial(0, currentMat);
	target->SetActorScale3D(FVector(0.5f));
}

