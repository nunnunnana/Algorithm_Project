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
		else
			SpawnActor(currentTarget, 100);
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

void AStackQueue::QueuePush()
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

void AStackQueue::QueuePop()
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

/* 액터 생성 */
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

/* 액터 제거 */
void AStackQueue::RemoveActor()
{
	// 배열 마지막 인덱스의 액터가 NULL 인지 확인 후 제거
	if (arrTarget[top] != nullptr) {
		arrTarget[top]->Destroy();
		arrTarget.RemoveAt(top);

		// 마지막 인덱스가 0이면 변수 초기화
		if (top == 0) {
			currentTarget = nullptr;
		}
		else {
			currentTarget = arrTarget[top - 1];
		}
	}
}
