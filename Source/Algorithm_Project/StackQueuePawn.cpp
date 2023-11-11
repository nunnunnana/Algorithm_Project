// Fill out your copyright notice in the Description page of Project Settings.


#include "StackQueuePawn.h"

// Sets default values
AStackQueuePawn::AStackQueuePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 블루프린트 클래스를 받아온다
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidgetAsset(TEXT("WidgetBlueprint'/Game/StackQueue/BP_W_StackQueue.BP_W_StackQueue_C'"));
	// TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어준다
	if (MainHUDWidgetAsset.Succeeded()) {
		MainHUDWidgetClass = MainHUDWidgetAsset.Class;
	}


}

// Called when the game starts or when spawned
void AStackQueuePawn::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainHUDWidgetClass))
	{
		MainHUDWidget = Cast<UW_StackQueue>(CreateWidget(GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			MainHUDWidget->AddToViewport();
			MainHUDWidget->SetAlertText(FText::FromString("babo"));
		}
	}
	
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