// Fill out your copyright notice in the Description page of Project Settings.


#include "W_StackQueue.h"

void UW_StackQueue::NativeConstruct()
{
	Super::NativeConstruct();
	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	convertButton->OnClicked.AddDynamic(this, &UW_StackQueue::SetButtonText);
	alertText->SetVisibility(ESlateVisibility::Hidden);
}
void UW_StackQueue::SetAlertText(FText text)
{
	alertText->SetVisibility(ESlateVisibility::Visible);
	alertText->SetText(text);

	// 타이머 초기화
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	// 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UW_StackQueue::AdvanceTimer, 1.0f, false, 3.0f);

}

void UW_StackQueue::AdvanceTimer()
{
	alertText->SetVisibility(ESlateVisibility::Hidden);
}

void UW_StackQueue::SetButtonText()
{
	if (isQueue == true) {
		stateText->SetText(FText::FromString("Stack"));
	}
	else {
		stateText->SetText(FText::FromString("Queue"));
	}
	isQueue = !isQueue;
}

