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

	// 머티리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> findMat(TEXT("/Script/Engine.Material'/Game/StackQueue/M_Base.M_Base'"));
	currentMat = findMat.Object;

	//staticMesh->SetStaticMesh(cubeMesh);
	//staticMesh->SetMaterial(0, currentMat);
}

// Called when the game starts or when spawned
void AStackQueue::BeginPlay()
{
	Super::BeginPlay();
	size = size + 1; // 입력값이랑 동기화 해주기 위해 설정
}

// Called every frame
void AStackQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*

	Stack

*/

// 스택이 가득 찼는지 확인
bool AStackQueue::IsStackFull()
{
	if (top >= size - 2)
		return true;
	else
		return false;
}

// 스택이 비어있는지 확인
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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsStackFull"));
		if (OnFulled.IsBound() == true)
			OnFulled.Execute();
	}
	else {
		// 처음 생성하면 현재 위치에 생성
		if (currentTarget == nullptr)
			SpawnStackActor(this, 0);
		// 기존에 생성한 액터가 있을 경우 위치 이동 후 생성
		else {
			// 생성하기 전에 기존 액터 색상 변경
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 1, 1));
			SpawnStackActor(currentTarget, 100);
		}
		top++;
	}
}

void AStackQueue::Pop()
{
	if (IsStackEmpty()) {
		if (OnEmptied.IsBound() == true)
			OnEmptied.Execute();
	}
	else {
		RemoveStackActor();
		top--;
	}
}

/* 스택 액터 생성 */
void AStackQueue::SpawnStackActor(AActor* targetActor, int height)
{
	FVector currentLocation = targetActor->GetActorLocation();
	currentLocation.Z += height; 
	SpawnActor(currentLocation, FVector(1, 0, 0));
}

/* 스택 액터 제거 */
void AStackQueue::RemoveStackActor()
{
	// 배열 마지막 인덱스의 액터가 NULL 인지 확인 후 제거
	if (arrTarget[top] != nullptr) {
		RemoveActor(top);

		// 마지막 인덱스가 0이면 변수 초기화
		if (top == 0) {
			currentTarget = nullptr;
		}
		else {
			currentTarget = arrTarget[top - 1];
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
		}
	}
}

/* 스택 비우기 */
void AStackQueue::ClearStack()
{
	ClearActors(top);
	top = -1;
}

/*

	Queue

*/

// 큐가 가득 찼는지 확인
bool AStackQueue::IsQueueFull()
{
	if ((rear + 1) % size == front) {
		return true;
	}
	return false;
}

// 큐가 비어있는지 확인
bool AStackQueue::IsQueueEmpty()
{
	if (rear == front) {
		return true;
	}
	return false;
}

void AStackQueue::Enqueue()
{
	if (IsQueueFull()) {
		if (OnFulled.IsBound() == true)
			OnFulled.Execute();
	}
	else {
		rear = (rear + 1) % size;
		// 처음 생성하면 현재 위치에 생성
		if (currentTarget == nullptr) {
			SpawnQueueActor(this, 0);
			// Rear Color 설정
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0, 0, 1));
		}
		// 기존에 생성한 액터가 있을 경우 위치 이동 후 생성
		else {
			// 생성하기 전에 기존 액터 색상 변경
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 1, 1));
			SpawnQueueActor(currentTarget, 100);
			// Front Color 설정
			arrTarget[0]->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
		}
	}

}

void AStackQueue::Dequeue()
{
	if (IsQueueEmpty()) {
		if (OnEmptied.IsBound() == true)
			OnEmptied.Execute();
	}
	else {
		front = (front + 1) % size;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), front));
		RemoveQueueActor();
	}

}

/* 큐 액터 생성 */
void AStackQueue::SpawnQueueActor(AActor* targetActor, int width)
{
	FVector currentLocation = targetActor->GetActorLocation();
	currentLocation.Y += width;
	SpawnActor(currentLocation, FVector(0, 0, 1));
}

/* 큐 액터 제거 */
void AStackQueue::RemoveQueueActor()
{
	// 마지막 인덱스면 삭제 후 currentTarget초기화
	if (IsQueueEmpty()) {
		RemoveActor(0);
		currentTarget = nullptr;
	}
	else {
		// 첫 번째 자리의 액터가 빠진 만큼 위치 이동
		for (int i = 0; i < arrTarget.Num(); i++) {
			arrTarget[i]->AddActorLocalOffset(FVector(0, -100, 0));
		}
		RemoveActor(0);
		// 제거 후 마지막 액터가 남았는지 확인 후 Color 설정
		if (arrTarget.Num() == 1)
			arrTarget[0]->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0, 0, 1));
		else
			arrTarget[0]->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
	}
}

/* 큐 비우기 */
void AStackQueue::ClearQueue()
{
	ClearActors(arrTarget.Num() - 1);
	front = 0;
	rear = 0;
}

/*

	Stack, Queue 같이 사용하는 함수

*/

// arrTarget 초기화
void AStackQueue::ClearActors(int num)
{
	for (int i = num; i > -1; i--) {
		RemoveActor(i);
	}
	currentTarget = nullptr;
}

// 액터 생성
void AStackQueue::SpawnActor(FVector location, FVector color)
{
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), location, rotation, SpawnParams);
	// 액터의 위치 이동을 위해 Movable로 설정
	target->SetMobility(EComponentMobility::Movable);
	target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh);
	target->GetStaticMeshComponent()->SetMaterial(0, currentMat);
	target->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), color);
	currentTarget = target;
	arrTarget.Add(currentTarget);
}

// 액터 제거
void AStackQueue::RemoveActor(int index)
{
	arrTarget[index]->Destroy();
	arrTarget.RemoveAt(index);
}
