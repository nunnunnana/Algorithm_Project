// Fill out your copyright notice in the Description page of Project Settings.

#include "StackQueue.h"
#include "Components/TimeLineComponent.h"

// Sets default values
AStackQueue::AStackQueue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	// ��Ƽ���� ����
	static ConstructorHelpers::FObjectFinder<UMaterial> findMat(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base.M_Base'"));
	currentMat = findMat.Object;

	//staticMesh->SetStaticMesh(cubeMesh);
	//staticMesh->SetMaterial(0, currentMat);
}

// Called when the game starts or when spawned
void AStackQueue::BeginPlay()
{
	Super::BeginPlay();
	size = size + 1; // �Է°��̶� ����ȭ ���ֱ� ���� ����


	// Ŀ�갡 ������ �� Ÿ�Ӷ����� ����
	if (curve != nullptr)
	{
		// ������ Curve�� ����� Callback �Լ�
		FOnTimelineFloat ProgressStackUpdate;
		FOnTimelineFloat ProgressEnqueueUpdate;
		FOnTimelineFloat ProgressDequeueUpdate;

		// Timeline�� ������ �� ������ Callback �Լ�
		FOnTimelineEvent StackFinished;
		FOnTimelineEvent DequeueFinished;

		// Ÿ�Ӷ��� Direction ����
		StackTimeline.SetPropertySetObject(this);
		StackTimeline.SetDirectionPropertyName(FName("StackTimelineDirection"));

		// Callback �Լ��� ����� �Լ��� ���ε�
		// ���ε� �ϴ� �Լ����� UFUNCTION ��ũ�ΰ� ����
		ProgressStackUpdate.BindUFunction(this, FName("StackUpdate"));
		ProgressEnqueueUpdate.BindUFunction(this, FName("EnqueueUpdate"));
		ProgressDequeueUpdate.BindUFunction(this, FName("DequeueUpdate"));
		StackFinished.BindUFunction(this, FName("StackFinished"));
		DequeueFinished.BindUFunction(this, FName("DequeueFinished"));

		// Timeline�� Curve�� Curve�� ����� Callback �Լ�
		StackTimeline.AddInterpFloat(curve, ProgressStackUpdate);
		EnqueueTimeline.AddInterpFloat(curve, ProgressEnqueueUpdate);
		DequeueTimeline.AddInterpFloat(curve, ProgressDequeueUpdate);

		// Timeline ������ ȣ���� Cabllback �Լ�
		StackTimeline.SetTimelineFinishedFunc(StackFinished);
		DequeueTimeline.SetTimelineFinishedFunc(DequeueFinished);
	
	}

	

}

// Called every frame
void AStackQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StackTimeline.TickTimeline(DeltaTime);
	EnqueueTimeline.TickTimeline(DeltaTime);
	DequeueTimeline.TickTimeline(DeltaTime);
}

/*

	Stack

*/

// ������ ���� á���� Ȯ��
bool AStackQueue::IsStackFull()
{
	if (top >= size - 2)
		return true;
	else
		return false;
}

// ������ ����ִ��� Ȯ��
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
	else if (!StackTimeline.IsPlaying()) {
		// ó�� �����ϸ� ���� ��ġ�� ����
		if (currentTarget == nullptr)
			SpawnStackActor(this, 0);
		// ������ ������ ���Ͱ� ���� ��� ��ġ �̵� �� ����
		else {
			// �����ϱ� ���� ���� ���� ���� ����
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
	else if(!StackTimeline.IsPlaying()) {
		StackTimeline.ReverseFromEnd();
	}
}

// ���� Ÿ�Ӷ��� ������Ʈ �Լ�
void AStackQueue::StackUpdate(float Alpha)
{
	currentTarget->SetActorLocation(FVector(0.0f, 0.0f, FMath::Lerp(currentZLocation, targetZLocation, Alpha)));
}

// Stack Ÿ�Ӷ��� ���� �Լ�
void AStackQueue::StackFinished()
{
	// Timeline�� Reverse �� ���� ����
	if (StackTimelineDirection == ETimelineDirection::Backward) {
		RemoveStackActor();
		top--;
	}

}

/* ���� ���� ���� */
void AStackQueue::SpawnStackActor(AActor* targetActor, int height)
{
	FVector currentLocation = targetActor->GetActorLocation();
	currentLocation.Z += height; 
	currentLocation.Z += 500.0f;
	SpawnActor(currentLocation, FVector(1, 0, 0));
	currentZLocation = currentTarget->GetActorLocation().Z;
	targetZLocation = currentTarget->GetActorLocation().Z - 500.0f;
	// Timeline ����
	StackTimeline.PlayFromStart();
}

/* ���� ���� ���� */
void AStackQueue::RemoveStackActor()
{
	// �迭 ������ �ε����� ���Ͱ� NULL ���� Ȯ�� �� ����
	if (arrTarget[top] != nullptr) {
		RemoveActor(top);

		// ������ �ε����� 0�̸� ���� �ʱ�ȭ
		if (top == 0) {
			currentTarget = nullptr;
		}
		else {
			currentTarget = arrTarget[top - 1];
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
			currentZLocation = currentTarget->GetActorLocation().Z + 500.0f;
			targetZLocation = currentTarget->GetActorLocation().Z;
		}
	}
}

/* ���� ���� */
void AStackQueue::ClearStack()
{
	ClearActors(top);
	top = -1;
}

/*

	Queue

*/

// ť�� ���� á���� Ȯ��
bool AStackQueue::IsQueueFull()
{
	if ((rear + 1) % size == front) {
		return true;
	}
	return false;
}

// ť�� ����ִ��� Ȯ��
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
	else if(!EnqueueTimeline.IsPlaying() && !DequeueTimeline.IsPlaying()){
		rear = (rear + 1) % size;
		// ó�� �����ϸ� ���� ��ġ�� ����
		if (currentTarget == nullptr) {
			SpawnQueueActor(this, 0);
			// Rear Color ����
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0, 0, 1));
		}
		// ������ ������ ���Ͱ� ���� ��� ��ġ �̵� �� ����
		else {
			// �����ϱ� ���� ���� ���� ���� ����
			currentTarget->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 1, 1));
			SpawnQueueActor(currentTarget, 100);
			// Front Color ����
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
	else if(!EnqueueTimeline.IsPlaying() && !DequeueTimeline.IsPlaying()) {
		front = (front + 1) % size;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), front));
		RemoveQueueActor();
	}

}

/* ť ���� ���� */
void AStackQueue::SpawnQueueActor(AActor* targetActor, int width)
{
	FVector currentLocation = targetActor->GetActorLocation();
	currentLocation.Y += width;
	currentLocation.Y += 500.0f;
	SpawnActor(currentLocation, FVector(0, 0, 1));
	currentYLocation = currentTarget->GetActorLocation().Y;
	targetYLocation = currentTarget->GetActorLocation().Y - 500.0f;
	// Timeline ����
	EnqueueTimeline.PlayFromStart();
}


// Enqueue Ÿ�Ӷ��� ������Ʈ �Լ�
void AStackQueue::EnqueueUpdate(float Alpha)
{
	currentTarget->SetActorLocation(FVector(0.0f, FMath::Lerp(currentYLocation, targetYLocation, Alpha), 0.0f));
}

/* ť ���� ���� */
void AStackQueue::RemoveQueueActor()
{
	currentYLocation = 0;
	targetYLocation = -500.0f;
	// Timeline�� ����
	DequeueTimeline.PlayFromStart();
}

// Dequeue Ÿ�Ӷ��� ������Ʈ �Լ�
void AStackQueue::DequeueUpdate(float Alpha)
{
	arrTarget[0]->SetActorLocation(FVector(0.0f, FMath::Lerp(currentYLocation, targetYLocation, Alpha), 0.0f));
}

// Dequeue Ÿ�Ӷ��� ���� �Լ�
void AStackQueue::DequeueFinished()
{
	// ������ �ε����� ���� �� currentTarget�ʱ�ȭ
	if (IsQueueEmpty()) {
		RemoveActor(0);
		currentTarget = nullptr;
	}
	else {
		// ù ��° �ڸ��� ���Ͱ� ���� ��ŭ ��ġ �̵�
		for (int i = 0; i < arrTarget.Num(); i++) {
			arrTarget[i]->AddActorLocalOffset(FVector(0, -100, 0));
		}
		RemoveActor(0);
		// ���� �� ������ ���Ͱ� ���Ҵ��� Ȯ�� �� Color ����
		if (arrTarget.Num() == 1)
			arrTarget[0]->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0, 0, 1));
		else
			arrTarget[0]->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0));
	}
}

/* ť ���� */
void AStackQueue::ClearQueue()
{
	ClearActors(arrTarget.Num() - 1);
	front = 0;
	rear = 0;
}

/*

	Stack, Queue ���� ����ϴ� �Լ�

*/

// arrTarget �ʱ�ȭ
void AStackQueue::ClearActors(int num)
{
	for (int i = num; i > -1; i--) {
		RemoveActor(i);
	}
	currentTarget = nullptr;
}

// ���� ����
void AStackQueue::SpawnActor(FVector location, FVector color)
{
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), location, rotation, SpawnParams);
	// ������ ��ġ �̵��� ���� Movable�� ����
	target->SetMobility(EComponentMobility::Movable);
	target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh);
	target->GetStaticMeshComponent()->SetMaterial(0, currentMat);
	target->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), color);
	currentTarget = target;
	arrTarget.Add(currentTarget);
}

// ���� ����
void AStackQueue::RemoveActor(int index)
{
	arrTarget[index]->Destroy();
	arrTarget.RemoveAt(index);
}
