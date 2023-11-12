// Fill out your copyright notice in the Description page of Project Settings.


#include "W_StackQueue.h"

void UW_StackQueue::NativeConstruct()
{
	Super::NativeConstruct();
	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	convertButton->OnClicked.AddDynamic(this, &UW_StackQueue::SetButtonText);
	alertText->SetVisibility(ESlateVisibility::Hidden);
}
void UW_StackQueue::SetAlertText(FText text)
{
	alertText->SetVisibility(ESlateVisibility::Visible);
	alertText->SetText(text);

	// Ÿ�̸� �ʱ�ȭ
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	// Ÿ�̸� ����
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

