// Fill out your copyright notice in the Description page of Project Settings.


#include "StackQueuePawn.h"

// Sets default values
AStackQueuePawn::AStackQueuePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// 블루프린트 클래스를 받아온다
	static ConstructorHelpers::FClassFinder<UUserWidget> stackqueueWidgetAsset(TEXT("WidgetBlueprint'/Game/StackQueue/BP_W_StackQueue.BP_W_StackQueue_C'"));
	// TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어준다
	if (stackqueueWidgetAsset.Succeeded()) {
		stackqueueWidgetClass = stackqueueWidgetAsset.Class;
	}


}

// Called when the game starts or when spawned
void AStackQueuePawn::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(stackqueueWidgetClass))
	{
		stackqueueWidget = Cast<UW_StackQueue>(CreateWidget(GetWorld(), stackqueueWidgetClass));

		if (IsValid(stackqueueWidget))
		{
			stackqueueWidget->AddToViewport();
		}
	}
	stackqueueActor->OnFulled.BindUFunction(this, FName("CallDeleFunc_OnFulled"));
	stackqueueActor->OnEmptied.BindUFunction(this, FName("CallDeleFunc_OnEmptied"));
	
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
	if (stackqueueWidget->isQueue) {
		stackqueueActor->QueuePush();
	}
	else {
		stackqueueActor->Push();
		int index = stackqueueActor->top + 1;
		FString indexString = FString::FromInt(index);
		stackqueueWidget->SetIndexText(FText::FromString(indexString));
	}
		

}

void AStackQueuePawn::X()
{
	if (stackqueueWidget->isQueue) {
		stackqueueActor->QueuePop();
	}
	else {
		stackqueueActor->Pop();
		int index = stackqueueActor->top + 1;
		FString indexString = FString::FromInt(index);
		stackqueueWidget->SetIndexText(FText::FromString(indexString));
	}
}

void AStackQueuePawn::CallDeleFunc_OnFulled()
{
	stackqueueWidget->SetAlertText(FText::FromString("Full"));
}

void AStackQueuePawn::CallDeleFunc_OnEmptied()
{
	stackqueueWidget->SetAlertText(FText::FromString("Empty"));
}
