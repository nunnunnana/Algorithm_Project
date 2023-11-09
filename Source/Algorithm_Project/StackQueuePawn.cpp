// Fill out your copyright notice in the Description page of Project Settings.


#include "StackQueuePawn.h"

// Sets default values
AStackQueuePawn::AStackQueuePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStackQueuePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStackQueuePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStackQueuePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Z", IE_Pressed, this, &AStackQueuePawn::Z);
	PlayerInputComponent->BindAction("X", IE_Pressed, this, &AStackQueuePawn::X);

}

void AStackQueuePawn::Z()
{
	stackqueueActor->Push();
}

void AStackQueuePawn::X()
{
	stackqueueActor->Pop();
}