// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"

// Sets default values
ABasicPawn::ABasicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ABasicPawn::MoveUp);
	PlayerInputComponent->BindAxis("Turn", this, &ABasicPawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasicPawn::LookUp);

}

void ABasicPawn::MoveForward(float AxisValue)
{
	AddActorLocalOffset(FVector(AxisValue * moveSpeed * GetWorld()->GetDeltaSeconds(), 0, 0));
}

void ABasicPawn::MoveRight(float AxisValue)
{
	AddActorLocalOffset(FVector(0, AxisValue * moveSpeed * GetWorld()->GetDeltaSeconds(), 0));
}

void ABasicPawn::MoveUp(float AxisValue)
{
	AddActorLocalOffset(FVector(0, 0, AxisValue * moveSpeed * GetWorld()->GetDeltaSeconds()));
}

void ABasicPawn::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue * mouseSpeed * GetWorld()->GetDeltaSeconds());
}

void ABasicPawn::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * mouseSpeed * GetWorld()->GetDeltaSeconds());
}

