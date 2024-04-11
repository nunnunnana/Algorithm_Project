// Fill out your copyright notice in the Description page of Project Settings.


#include "W_StackQueue.h"

void UW_StackQueue::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass로 월드에 있는 AStackQueue 액터 찾기
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AStackQueue::StaticClass());
	// AStackQueue로 형변환
	stackqueueActor = Cast<AStackQueue>(FoundActor);

	//stackqueueActor = Cast(UGameplayStatics::GetActorOfClass(GetWorld(), AStackQueue::StaticClass()));
	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	convertButton->OnClicked.AddDynamic(this, &UW_StackQueue::SetButtonText);
	pushButton->OnClicked.AddDynamic(this, &UW_StackQueue::PressPushButton);
	popButton->OnClicked.AddDynamic(this, &UW_StackQueue::PressPopButton);
	//alertPanel->SetVisibility(ESlateVisibility::Hidden);
	queuePanel->SetVisibility(ESlateVisibility::Hidden);
}
void UW_StackQueue::SetAlertText(FText text)
{
	//alertPanel->SetVisibility(ESlateVisibility::Visible);
	alertText->SetText(text);
	PlayAnimation(alertWarning);
	// 타이머 초기화
	//GetWorld()->GetTimerManager().ClearTimer(Timer);
	// 타이머 설정
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &UW_StackQueue::AdvanceTimer, 1.0f, false, 3.0f);

}

void UW_StackQueue::SetIndexText(int index)
{
	FString indexString = FString::FromInt(index);
	indexText->SetText(FText::FromString(indexString));
}

void UW_StackQueue::AdvanceTimer()
{
	//alertPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UW_StackQueue::SetButtonText()
{
	if (isQueue == true) {
		stackqueueActor->ClearQueue();
		stateText->SetText(FText::FromString("Stack"));
		stackPanel->SetVisibility(ESlateVisibility::Visible);
		queuePanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		stackqueueActor->ClearStack();
		SetIndexText(0);
		stateText->SetText(FText::FromString("Queue"));
		stackPanel->SetVisibility(ESlateVisibility::Hidden);
		queuePanel->SetVisibility(ESlateVisibility::Visible);
	}
	isQueue = !isQueue;
}

void UW_StackQueue::PressPushButton()
{
	if (isQueue) {
		stackqueueActor->Enqueue();
	}
	else {
		stackqueueActor->Push();
		int index = stackqueueActor->top + 1;
		SetIndexText(index);

	}
}

void UW_StackQueue::PressPopButton()
{
	if (isQueue) {
		stackqueueActor->Dequeue();
	}
	else {
		stackqueueActor->Pop();
		// Delay
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				int index = stackqueueActor->top + 1;
				SetIndexText(index);
			}, 0.1, false);
	}
}

