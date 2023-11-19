// Fill out your copyright notice in the Description page of Project Settings.

#include "StackQueue.h"

// Sets default values
AStackQueue::AStackQueue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	staticMesh->SetupAttachment(RootComponent);

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

	static ConstructorHelpers::FObjectFinder<UMaterial> redMat(TEXT("/Script/Engine.Material'/Game/StackQueue/M_Base.M_Base'"));
	redMaterial = redMat.Object;

	//staticMesh->SetStaticMesh(cubeMesh);
	//staticMesh->SetMaterial(0, redMaterial);
}

// Called when the game starts or when spawned
void AStackQueue::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStackQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Stack
bool AStackQueue::IsStackFull()
{
	if (top >= size - 1)
		return true;
	else
		return false;
}

bool AStackQueue::IsStackEmpty()
{
	if (top < 0)
		return true;
	else
		return false;
}

void AStackQueue::Push()
{
	if (IsStackFull()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsStackFull"));
		if (OnFulled.IsBound() == true)
			OnFulled.Execute();
	}
	else {
		if (currentTarget == nullptr)
			SpawnActor(this, 0);
		else {
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 1, 1));
			SpawnActor(currentTarget, 100);
		}
		top++;
	}
}

void AStackQueue::Pop()
{
	if (IsStackEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsStackEmpty"));
		if (OnEmptied.IsBound() == true)
			OnEmptied.Execute();
	}

	else {
		RemoveActor();
		top--;
	}
}

//  Queue
bool AStackQueue::IsQueueFull()
{
	if ((rear + 1) % size == front) {
		return true;
	}
	return false;
}

bool AStackQueue::IsQueueEmpty()
{
	if (rear == front) {
		return true;
	}
	return false;
}

void AStackQueue::Enqueue()
{
	if (IsQueueFull()){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsQueueFull"));
		if (OnFulled.IsBound() == true)
			OnFulled.Execute();
	}
	else {
		rear = (rear + 1) % size;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"),rear));
	}

}

void AStackQueue::Dequeue()
{
	if (IsQueueEmpty()){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsQueueEmpty"));
		if (OnEmptied.IsBound() == true)
			OnEmptied.Execute();
	}
	else {
		front = (front + 1) % size;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), front));
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
	target->GetStaticMeshComponent()->SetMaterial(0, redMaterial);
	target->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1,0,0));
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
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
		}
	}
}

/* ���� ���� */
void AStackQueue::ClearStack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), top));
	if (top > -1) {
		for (int i = top; i > -1; i--) {
			arrTarget[i]->Destroy();
			arrTarget.RemoveAt(i);
		}
		top = -1;
		currentTarget = nullptr;
	}
}