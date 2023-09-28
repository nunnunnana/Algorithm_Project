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

void AStackQueue::IsEmpty()
{
	if (top < 0)
		check = true;
	else
		check = false;
}

void AStackQueue::IsFull()
{
	if (top >= 9)
		check = true;
	else
		check = false;
}

void AStackQueue::push() 
{
	if (check == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsFull"));
	else
		Stack.Add(++top);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("top = %d"), top));
}

void AStackQueue::pop()
{
	if (check == true)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsEmpty"));
	else
		Stack.RemoveAt(top--);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("top = %d"), top));
}

