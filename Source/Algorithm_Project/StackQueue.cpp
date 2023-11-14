// Fill out your copyright notice in the Description page of Project Settings.

#include "StackQueue.h"

// Sets default values
AStackQueue::AStackQueue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	staitcMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	staitcMesh->SetupAttachment(RootComponent);

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

	//staitcMesh->SetStaticMesh(cubeMesh);

}

// Called when the game starts or when spawned
void AStackQueue::BeginPlay()
{
	Super::BeginPlay();
	top = -1;
}

// Called every frame
void AStackQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AStackQueue::IsEmpty()
{
	if (top < 0)
		return true;
	else
		return false;
}

bool AStackQueue::IsFull()
{
	if (top >= size - 1)
		return true;
	else
		return false;
}

void AStackQueue::Push() 
{
	if (IsFull()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsFull"));
		if (OnFulled.IsBound() == true)
			OnFulled.Execute();
	}
	else {
		if (currentTarget == nullptr)
			SpawnActor(this, 0);
		else
			SpawnActor(currentTarget, 100);
		top++;
	}
}

void AStackQueue::Pop()
{
	if (IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsEmpty"));
		if (OnEmptied.IsBound() == true)
			OnEmptied.Execute();
	}
		
	else {
		RemoveActor();
		top--;
	}
}

/* ���� ���� */
void AStackQueue::SpawnActor(AActor* targetActor, int height)
{
	FVector currentLocation = targetActor->GetActorLocation();
	FRotator currentRotation = targetActor->GetActorRotation();
	currentLocation.Z += height;
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), currentLocation, currentRotation, SpawnParams);
	target->SetMobility(EComponentMobility::Movable);
	target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh);
	currentTarget = target;
	arrTarget.Add(currentTarget);
}

/* ���� ���� */
void AStackQueue::RemoveActor()
{
	// �迭 ������ �ε����� ���Ͱ� NULL ���� Ȯ�� �� ����
	if (arrTarget[top] != nullptr) {
		arrTarget[top]->Destroy();
		arrTarget.RemoveAt(top);

		// ������ �ε����� 0�̸� ���� �ʱ�ȭ
		if (top == 0) {
			currentTarget = nullptr;
		}
		else {
			currentTarget = arrTarget[top - 1];
		}
	}
}
