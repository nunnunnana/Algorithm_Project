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
		SpawnActor();
		top++;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("top = %d"), top));
	
}

void AStackQueue::Pop()
{
	if (IsEmpty())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsEmpty"));
	else {
		RemoveActor();
		top--;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("top = %d"), top));
}

void AStackQueue::SpawnActor()
{
	if (currentTarget == nullptr) {
		FVector currentLocation = GetActorLocation();
		FRotator currentRotation = GetActorRotation();
		currentLocation.Z += 50;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = NULL;
		SpawnParams.Instigator = NULL;
		AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), currentLocation, currentRotation, SpawnParams);
		target->SetMobility(EComponentMobility::Movable);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		if (cubeMesh.Succeeded())
		{
			target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh.Object);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CubeMeshAsset Succeeded")));
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CubeMeshAsset Failed")));
		currentTarget = target;
	}
	else if (currentTarget != nullptr) {
		FVector targetLocation = currentTarget->GetActorLocation();
		FRotator targetRotation = currentTarget->GetActorRotation();
		targetLocation.Z += 100;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = NULL;
		SpawnParams.Instigator = NULL;
		AStaticMeshActor* target = (AStaticMeshActor*)GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), targetLocation, targetRotation, SpawnParams);
		target->SetMobility(EComponentMobility::Movable);
		static ConstructorHelpers::FObjectFinder<UStaticMesh>cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		if (cubeMesh.Succeeded())
		{
			target->GetStaticMeshComponent()->SetStaticMesh(cubeMesh.Object);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CubeMeshAsset Succeeded")));
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CubeMeshAsset Failed")));
		currentTarget = target;
	}
	arrTarget.Add(currentTarget);
}


void AStackQueue::RemoveActor()
{
	if (arrTarget[top] != nullptr) {
		arrTarget[top]->Destroy();
		arrTarget.RemoveAt(top);
	}

}
