// Fill out your copyright notice in the Description page of Project Settings.


#include "Search_Points.h"

// Sets default values
ASearch_Points::ASearch_Points()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	costText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CostText"));

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

	staticMesh->SetStaticMesh(cubeMesh);
	staticMesh->SetupAttachment(RootComponent);
	// Set as root component
	// RootComponent = staticMesh;

	// 머티리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> white(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_White.M_Base_White'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> yellow(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_Yellow.M_Base_Yellow'"));
	currentMat = white.Object;
	yellowMat = yellow.Object;
	staticMesh->SetMaterial(0, currentMat);

	// Set scale
	SetActorScale3D(FVector(0.5f));

	// Set text
	costText->SetupAttachment(RootComponent);
	costText->SetWorldSize(100.0f);
	costText->SetTextRenderColor(FColor::Black);
	costText->SetHorizontalAlignment(EHTA_Center);
	costText->SetRelativeLocationAndRotation(FVector(0, 0, 90), FQuat(90.f, 0.f, 179.f, 0.f));

}

// Called when the game starts or when spawned
void ASearch_Points::BeginPlay()
{
	Super::BeginPlay();
	SetCostVisibility(false);
	//FVector currentLocation = this->GetActorLocation();
	//SpawnActor(currentLocation, FVector(0, 0, 0));

}

// Called every frame
void ASearch_Points::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString costString = FString::FromInt(cost);
	costText->SetText(FText::FromString(costString));
}


// 액터 생성
void ASearch_Points::SpawnActor(FVector location, FVector color)
{
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), location, rotation, SpawnParams);
	// 액터의 위치 이동을 위해 Movable로 설정
	target->SetMobility(EComponentMobility::Movable);
	target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh);
	target->GetStaticMeshComponent()->SetMaterial(0, currentMat);
	target->SetActorScale3D(FVector(0.5f));
}

void ASearch_Points::SetVisited()
{
	isVisited = true;
	SetMaterial(yellowMat);

}

void ASearch_Points::SetMaterial(UMaterialInstance* matrial)
{
	staticMesh->SetMaterial(0, matrial);
}

void ASearch_Points::SetCostVisibility(bool isVisibility)
{
	costText->SetVisibility(isVisibility);
}

