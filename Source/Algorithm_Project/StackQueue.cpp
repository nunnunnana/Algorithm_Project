// Fill out your copyright notice in the Description page of Project Settings.

#include "StackQueue.h"


// Sets default values
AStackQueue::AStackQueue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (top >= size)
		return true;
	else
		return false;
}

void AStackQueue::Push() 
{
	if (IsFull())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsFull"));
	else {
		if (currentTarget == nullptr)
			SpawnActor(this, 50);
		else
			SpawnActor(currentTarget, 100);
		top++;
	}
}

void AStackQueue::Pop()
{
	if (IsEmpty())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsEmpty"));
	else {
		RemoveActor();
		top--;
	}
}

void AStackQueue::SpawnActor(AActor* targetActor, int height)
{
	FVector currentLocation = targetActor->GetActorLocation();
	FRotator currentRotation = targetActor->GetActorRotation();
	currentLocation.Z += height;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NULL;
	SpawnParams.Instigator = NULL;
	AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), currentLocation, currentRotation, SpawnParams);
	target->SetMobility(EComponentMobility::Movable);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (cubeMesh.Succeeded())
	{
		target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh.Object);
	}
	currentTarget = target;
	arrTarget.Add(currentTarget);
}


void AStackQueue::RemoveActor()
{
	if (arrTarget[top] != nullptr) {
		arrTarget[top]->Destroy();
		arrTarget.RemoveAt(top);
	}
}
